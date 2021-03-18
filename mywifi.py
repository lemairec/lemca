

class MyWifiList():
    def get_list_wifis(self):
        return ["wifi1", "wifi2", "wifi3", "wifi4", "wifi5"]

    def connect_wifi(self, ssid, password):
        return "ok"

def test_wifi():
    wifi = MyWifiList()
    wifis = wifi.get_list_wifis()
    for wifi in wifis:
        print(wifi)

test_wifi()