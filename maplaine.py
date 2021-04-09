def save_gps_parcelles():
    url_parcelles_get = url+"/parcelles_gps?name=lemaire@abvent.fr"
    my_parcelles_job = my_dir+"/parcelle"
    
    parcelles_local = []
    dirs = os.listdir(my_parcelles_job)
    for file_info in dirs:
        with open(my_parcelles_job+"/"+file_info) as fp:
            line0 = fp.readline()
            if(line0.startswith("[PARCELLE]")):
                parcelle_dates = fp.readline().split(" ")
                if(parcelle_dates[0]=="DATE"):
                    name = file_info.replace(".txt", "")
                    date = parcelle_dates[1].replace("\n", "")
                    parcelles_local.append({"name":name, "datetime":date})
            

    
    r=requests.get(url_parcelles_get)
    parcelles_web = r.json()

    
    print("local")
    print(parcelles_local)
    print("web")
    print(parcelles_web)

    for parcelle_local in parcelles_local:
        find=False
        for parcelle_web in parcelles_web:
            if(parcelle_web["name"] == parcelle_local["name"]):
                find=True
        if(not find):
            print("faut push "+parcelle_local["name"])

    for parcelle_web in parcelles_web:
        find=False
        for parcelle_local in parcelles_local:
            if(parcelle_web["name"] == parcelle_local["name"]):
                find=True
        if(not find):
            print("faut get "+parcelle_local["name"])
    

                    
                    

def save_gps_jobs():
    url_job = url+"/job_gps"
    my_dir_job = my_dir+"/job"
    dirs = os.listdir(my_dir_job)

    for file_info in dirs:
        if(file_info.endswith(".info")):
            file_info = my_dir+file_info
            file_job = file_info.replace(".info", ".job")
            file_debug = file_info.replace(".info", ".debug")
            print(file_info)
            print(file_job)
            print(file_debug)

            
            ok_text = ""
            debug = ""
            with open(file_debug) as f:
                debug = f.read()

            with open(file_info) as f:
                read_data = f.read()
                mydata = json.loads(read_data)
                with open(file_job) as f_job:
                    mydata_job = f_job.read()

                    mydata["job"]=mydata_job
                    mydata["debug"]=debug
                    mydata["user_email"]=user_email
                    print(mydata)

                    r=requests.post(url_job,data=mydata)
                    
                    ok_text = r.text

            if(ok_text == "\"ok\""):
                os.remove(file_info)
                os.remove(file_job)
                os.remove(file_debug)
            else:
                print("not_ok")
                print(ok_text)