#include "Folder.hpp"

/**
* @brief Construct a new Folder object
* @param name A string with alphanumeric characters.
   If the folder name is empty / none is provided, default value of "NewFolder" is used. 
* @throw If the name is invalid (eg. contains non-alphanumeric characters) an InvalidFormatException is thrown
*/
Folder::Folder(const std::string& name) : name_{"NewFolder"} {
   if (name.empty()) { return; }

   for (const char& c : name) {
      if (!std::isalnum(c)) {
         // We have found a non-alphanumeric character
         throw InvalidFormatException("Invalid folder name: " + name);
      }
   }
   
   name_ = name;
}

/**
   * @brief Get the value stored in name_
   * @return std::string 
   */
std::string Folder::getName() const {
   return name_;
}

/**
* @brief Sets the name_ member to the given parameter
* 
* @param new_foldername A string containing only alphanumeric characters
*    - If the string is invalid the folder is not renamed
* @return True if the folder was renamed sucessfully. False otherwise.
*/
bool Folder::rename(const std::string& name) {
   for (const char& c : name) {
      if (!std::isalnum(c)) { return false; }
   }
   
   name_ = name;
   return true;
}

/**
* @brief Sorts and prints the names of subfolder and file vectors lexicographically (ie. alphabetically)
* The contents of subfolders are not printed.
* Reference the following format (using 3 spaces to indent the contained filenames)
* <CURRENT_FOLDER_NAME> 
*    <SUBFOLDER1_NAME> 
*    <SUBFOLDER2_NAME> 
*    ...
*    <SUBFOLDER_N_NAME> 
*    <FILENAME_1>
*    <FILENAME_2>
*     ...
*    <FILENAME_N>
* 
* @note: This CAN be done more efficiently by maintaining sorted order in the vectors already, instead of sorting each time we print. 
*    However, we'll hold off on that for now, since we just want to get used to iterating with iterators.
*/
void Folder::display() {
   std::sort(files_.begin(), files_.end());

   std::cout << getName() << std::endl;
   for (auto it = files_.begin(); it != files_.end(); ++it) { std::cout << "   " << it->getName() << std::endl; }
}

//                       DO NOT EDIT ABOVE THIS LINE. 
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp
// =========================== YOUR CODE HERE ===========================

size_t Folder::getSize () const {
   size_t total_size = 0;
    for (const auto &file : files_) {
        total_size += file.getSize();
    }
    return total_size;
}

bool Folder::addFile(File&& new_file) {
   if (new_file.getName().empty()) {
        return false;
    }
    
    // Check for existence
    for (const auto &file : files_) {
        if (file.getName() == new_file.getName()) {
            return false;
        }
    }
    
    files_.push_back(std::move(new_file)); 
    return true;
}

bool Folder::removeFile(const std::string& name) {
   auto it = std::remove_if(files_.begin(), files_.end(),
        [&name](const File &file) { return file.getName() == name; });
    
    if (it != files_.end()) {
        files_.erase(it, files_.end());
        return true;
    }
    
    return false;
}

bool Folder::moveFileTo(const std::string& name, Folder& destination){
   // If source and destination are the same folder
    if (this == &destination) {
        return true;
    }
    
    // Check if file exists in the current folder
    auto it = std::find_if(files_.begin(), files_.end(),
        [&name](const File &file) { return file.getName() == name; });

    if (it == files_.end()) {
        return false; // File not found in the current folder
    }

    // Check if file with the same name already exists in the destination folder
    for (const auto &file : destination.files_) {
        if (file.getName() == name) {
            return false; // File already exists in the destination folder
        }
    }

    // Move the file to the destination folder
    destination.files_.push_back(std::move(*it));
    files_.erase(it); // Remove from current folder
    return true;
}

bool Folder::copyFileTo(const std::string &name, Folder &destination) const {
   // Check if file exists in the current folder
    auto it = std::find_if(files_.begin(), files_.end(),
        [&name](const File &file) { return file.getName() == name; });

    if (it == files_.end()) {
        return false; // File not found in the current folder
    }

    // Check if file with the same name already exists in the destination folder
    for (const auto &file : destination.files_) {
        if (file.getName() == name) {
            return false; // File already exists in the destination folder
        }
    }

    // Copy the file to the destination folder (deep copy)
    destination.files_.push_back(*it);
    return true;
}