#include "File.hpp"

std::string File::getName() const
{
   return filename_;
}

std::string File::getContents() const
{
   return contents_;
}

void File::setContents(const std::string &new_contents)
{
   contents_ = new_contents;
}

int *File::getIcon() const
{
   return icon_;
}

void File::setIcon(int *new_icon)
{
   if (icon_)
   {
      delete[] icon_;
   }
   icon_ = new_icon;
}

std::ostream &operator<<(std::ostream &os, const File &target)
{
   os << "Name: " << target.getName() << std::endl;
   os << "Size: " << target.getSize() << " bytes" << std::endl;
   os << "Contents: " << target.getContents();
   return os;
}

bool File::operator<(const File &rhs) const
{
   return getName() < rhs.getName();
}

//                       DO NOT EDIT ABOVE THIS LINE.
//             (unless you want your work to be tested incorrectly)
//    That also means includes. Remember, all other includes go in .hpp

// However, you may notice an operator overload you don't recognize (<<)
// Try calling the following once you've implemented a constructor & getSize():
//    File a;
//    std::cout << a << std::endl;

// =========================== YOUR CODE HERE ===========================

File::File(const std::string &filename_, const std::string &contents_, int *icon_)
    : filename_(filename_), contents_(contents_), icon_(icon_ ? new int(*icon_) : nullptr) {}

size_t File::getSize() const
{
   return contents_.size();
}

File::File(const File &rhs)
    : filename_(rhs.filename_), contents_(rhs.contents_), icon_(rhs.icon_ ? new int(*rhs.icon_) : nullptr) {}

File &File::operator=(const File &rhs)
{
   if (this != &rhs)
   {
      filename_ = rhs.filename_;
      contents_ = rhs.contents_;

      // Safely handle the icon copy
      int *temp_icon = rhs.icon_ ? new int(*rhs.icon_) : nullptr;
      delete icon_;
      icon_ = temp_icon;
   }
   return *this;
}

File::File(File &&rhs)
    : filename_(std::move(rhs.filename_)), contents_(std::move(rhs.contents_)), icon_(rhs.icon_)
{
   rhs.icon_ = nullptr; // Prevent double deletion by nullifying the moved-from object's pointer
}

File &File::operator=(File &&rhs)
{
   if (this != &rhs)
   {
      filename_ = std::move(rhs.filename_);
      contents_ = std::move(rhs.contents_);

      delete icon_; // Clean up old memory
      icon_ = rhs.icon_;
      rhs.icon_ = nullptr; // Prevent double deletion
   }
   return *this;
}

File::~File()
{
   delete icon_;
}
