#ifndef DIRECTORY_MANAGER_H
#define DIRECTORY_MANAGER_H

#include <string>

class DirectoryManager {
    DirectoryManager();
    void readFile();
    
    std::string m_bin_dir;
    std::string m_source_dir;
    std::string m_reload_dir;
public:
    static DirectoryManager & Instance();
    ~DirectoryManager();
    
    std::string m_log_file;
    
    const std::string & getBinDirectory();
    const std::string & getSourceDirectory();
};

#endif //UTIL_H
