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
   os << "Size: " << target.getFileSize() << " bytes" << std::endl;
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

File::File(const std::string &filename, const std::string &contents, int *icon)
    : filename_("NewFile.txt"), contents_(contents), icon_(nullptr)
{
    // Check for an empty filename
    if (filename.empty())
    {
        return; // The default value will be used
    }

    // Validate the filename format
    size_t period_pos = filename.find('.');
    if (period_pos == std::string::npos || period_pos == 0 || period_pos == filename.size() - 1)
    {
        throw InvalidFormatException("Invalid filename format: " + filename);
    }

    // Ensure only alphanumeric characters and one period
    for (char c : filename)
    {
        if (!std::isalnum(c) && c != '.')
        {
            throw InvalidFormatException("Invalid filename format: " + filename);
        }
    }

    // Set the filename if valid
    filename_ = filename;

    // Handle icon
    if (icon)
    {
        icon_ = new int[ICON_DIM];
        std::memcpy(icon_, icon, ICON_DIM * sizeof(int));
    }

    // Set the extension to ".txt" if none is provided
    if (period_pos == std::string::npos || period_pos == filename.size() - 1)
    {
        filename_ += ".txt";
    }
}

size_t File::getFileSize() const
{
   return contents_.size();
}


File::File(const File &rhs)
    : filename_(rhs.filename_), contents_(rhs.contents_), icon_(nullptr)
{
   if (rhs.icon_)
   {
      icon_ = new int[ICON_DIM];
      std::memcpy(icon_, rhs.icon_, ICON_DIM * sizeof(int));
   }
}

File &File::operator=(const File &rhs)
{
   if (this != &rhs)
   {
      filename_ = rhs.filename_;
      contents_ = rhs.contents_;
      if (icon_)
      {
         delete[] icon_;
      }
      if (rhs.icon_ != nullptr)
      {
         icon_ = new int[ICON_DIM];
         std::memcpy(icon_, rhs.icon_, ICON_DIM * sizeof(int));
      }
      else
      {
         icon_ = nullptr;
      }
   }
   return *this;
}


File::File(File &&rhs)
    : filename_(std::move(rhs.filename_)), contents_(std::move(rhs.contents_)), icon_(rhs.icon_)
{
   rhs.icon_ = nullptr;
}

File &File::operator=(File &&rhs)
{
   if (this != &rhs)
   {
      filename_ = std::move(rhs.filename_);
      contents_ = std::move(rhs.contents_);
      if (icon_)
      {
         delete[] icon_;
      }
      icon_ = rhs.icon_;
      rhs.icon_ = nullptr;
   }
   return *this;
}

File::~File()
{
   delete[] icon_;
}