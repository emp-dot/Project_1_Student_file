#include <iostream>
#include <cassert>
#include "File.hpp"
#include "Folder.hpp"

void testFileConstructorsAndAssignment() {
    // Test default constructor
    File file1;
    assert(file1.getName() == "NewFile.txt");

    // Test parameterized constructor
    int icon[] = {1, 2, 3, 4};
    File file2("testFile.txt", "Hello, World!", icon);
    assert(file2.getName() == "testFile.txt");
    assert(file2.getContents() == "Hello, World!");

    // Test invalid filename (throws exception)
    try {
        File file3("invalidFileName#", "Content");
        assert(false); // Should not reach here
    } catch (const InvalidFormatException &e) {
        std::cout << "Caught expected exception for invalid filename: " << e.what() << std::endl;
    }

    // Test copy constructor
    File file3 = file2;
    assert(file3.getName() == file2.getName());
    assert(file3.getContents() == file2.getContents());

    // Test move constructor
    File file4 = std::move(file2);
    assert(file4.getName() == "testFile.txt");
    assert(file2.getName().empty()); // Moved file should be in a valid state, name empty

    // Test copy assignment operator
    file1 = file3;
    assert(file1.getName() == file3.getName());
    assert(file1.getContents() == file3.getContents());

    // Test move assignment operator
    file1 = std::move(file4);
    assert(file1.getName() == "testFile.txt");
    assert(file4.getName().empty()); // Moved file should be in a valid state

    // Test self-assignment copy
    file1 = file1;
    assert(file1.getName() == "testFile.txt");

    // Test self-assignment move
    file1 = std::move(file1);
    assert(file1.getName() == "testFile.txt");

    std::cout << "File constructors and assignment operators tests passed!" << std::endl;
}

void testFolderOperations() {
    Folder folder1("MyFolder");
    Folder folder2("DestinationFolder");

    // Test adding files
    File file1("file1.txt", "Content1");
    File file2("file2.txt", "Content2");
    assert(folder1.addFile(file1));
    assert(!folder1.addFile(file1)); // Should fail (duplicate)

    // Test removing files
    assert(folder1.removeFile("file1.txt"));
    assert(!folder1.removeFile("file1.txt")); // Already removed

    // Test moving files
    folder1.addFile(file2);
    assert(folder1.moveFileTo("file2.txt", folder2));
    assert(!folder1.moveFileTo("nonexistent.txt", folder2)); // File doesn't exist

    // Test copying files
    folder1.addFile(file1);
    assert(folder1.copyFileTo("file1.txt", folder2));
    assert(!folder1.copyFileTo("file1.txt", folder2)); // Duplicate in destination

    // Test folder size
    assert(folder1.getSize() == file1.getFileSize());
    assert(folder2.getSize() == file1.getFileSize() + file2.getFileSize());

    std::cout << "Folder operations tests passed!" << std::endl;
}

int main() {
    testFileConstructorsAndAssignment();
    testFolderOperations();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
