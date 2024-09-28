#include "Folder.hpp"

/**
* @brief Construct a new Folder object
* @param name A string with alphanumeric characters.
   If the folder name is empty / none is provided, default value of "NewFolder" is used.
* @throw If the name is invalid (eg. contains non-alphanumeric characters) an InvalidFormatException is thrown
*/
Folder::Folder(const std::string &name) : name_{"NewFolder"}
{
   if (name.empty())
   {
      return;
   }

   for (const char &c : name)
   {
      if (!std::isalnum(c))
      {
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
std::string Folder::getName() const
{
   return name_;
}

/**
 * @brief Sets the name_ member to the given parameter
 *
 * @param new_foldername A string containing only alphanumeric characters
 *    - If the string is invalid the folder is not renamed
 * @return True if the folder was renamed sucessfully. False otherwise.
 */
bool Folder::rename(const std::string &name)
{
   for (const char &c : name)
   {
      if (!std::isalnum(c))
      {
         return false;
      }
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
void Folder::display()
{
   std::sort(files_.begin(), files_.end());

   std::cout << getName() << std::endl;
   for (auto it = files_.begin(); it != files_.end(); ++it)
   {
      std::cout << "   " << it->getName() << std::endl;
   }
}

//                       DO NOT EDIT ABOVE THIS LINE.
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp
// =========================== YOUR CODE HERE ===========================


size_t Folder::getSize() const
{
   size_t totalSize = 0;
   for (const auto &file : files_)
   {
      totalSize += file.getFileSize(); // Assuming File has a getSize() method
   }
   return totalSize;
}

bool Folder::addFile(File new_file)
{
   // Check if the file's name is empty
   if (new_file.getName().empty())
   {
      return false;
   }

   // Check for duplicate file names
   for (const auto &file : files_)
   {
      if (file.getName() == new_file.getName())
      {
         return false; // File with the same name exists
      }
   }

   files_.push_back(std::move(new_file)); // Move semantics
   return true;
}

bool Folder::removeFile(const std::string &name)
{
   // Iterate through the files vector to find the file to remove
   for (auto it = files_.begin(); it != files_.end(); ++it)
   {
      if (it->getName() == name)
      {
         // If a matching file is found, erase it and return true
         files_.erase(it);
         return true;
      }
   }
   // If no matching file is found, return false
   return false;
}

bool Folder::moveFileTo(const std::string &name, Folder &destination)
{
   // Check if the source and destination folders are the same
   if (this == &destination)
   {
      return true; // Moving within the same folder is considered successful
   }

   // Iterate through the files vector to find the file to move
   for (auto it = files_.begin(); it != files_.end(); ++it)
   {
      if (it->getName() == name)
      {
         // Check for duplicates in the destination folder
         for (const auto &file : destination.files_)
         {
            if (file.getName() == name)
            {
               return false; // File with the same name exists in destination
            }
         }

         // Move the file using move semantics
         destination.files_.push_back(std::move(*it)); // Move semantics
         files_.erase(it);                             // Remove from current folder
         return true;                                  // File moved successfully
      }
   }

   return false; // File not found
}

bool Folder::copyFileTo(const std::string &name, Folder &destination)
{
   // Iterate through the files vector to find the file to copy
   for (const auto &file : files_)
   {
      if (file.getName() == name)
      {
         // Check for duplicates in the destination folder
         for (const auto &destFile : destination.files_)
         {
            if (destFile.getName() == name)
            {
               return false; // File with the same name exists in destination
            }
         }

         // Use the copy constructor to create a deep copy
         destination.files_.push_back(file); // Assuming File has a copy constructor
         return true;
      }
   }

   return false; // File not found
}
