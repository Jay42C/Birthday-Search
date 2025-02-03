//Birthday Search Program 
//


#include <iostream>
#include <string>


class Person {
public:
    std::string name;
    std::string birthday;

    Person(const std::string& n, const std::string& b) : name(n), birthday(b) {}
};

class TreeNode {
public:
    Person data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Person p) : data(p), left(nullptr), right(nullptr) {}
};

class Dictionary {
private:
    TreeNode* root;

    TreeNode* addEntry(TreeNode* node, const Person& person) {
        if (node == nullptr) {
            return new TreeNode(person);
        }

        if (person.name < node->data.name) {
            node->left = addEntry(node->left, person);
        } else if (person.name > node->data.name) {
            node->right = addEntry(node->right, person);
        }

        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode* removeEntry(TreeNode* node, const std::string& name) {
        if (node == nullptr) {
            return nullptr;
        }

        if (name < node->data.name) {
            node->left = removeEntry(node->left, name);
        } else if (name > node->data.name) {
            node->right = removeEntry(node->right, name);
        } else {
            if (node->left == nullptr) {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeEntry(node->right, temp->data.name);
        }

        return node;
    }

    void displayEntries(TreeNode* node) {
        if (node != nullptr) {
            displayEntries(node->left);
            std::cout << "Name: " << node->data.name << ", Birthday: " << node->data.birthday << std::endl;
            displayEntries(node->right);
        }
    }

    void displayMonthEntries(TreeNode* node, const std::string& month) {
        if (node != nullptr) {
            displayMonthEntries(node->left, month);
            if (node->data.birthday.substr(0, 2) == month) {
                std::cout << "Name: " << node->data.name << ", Birthday: " << node->data.birthday << std::endl;
            }
            displayMonthEntries(node->right, month);
        }
    }

public:
    Dictionary() : root(nullptr) {}

    void addEntry(const Person& person) {
        root = addEntry(root, person);
    }

    void removeEntry(const std::string& name) {
        root = removeEntry(root, name);
    }

    void searchByName(const std::string& name) {
        TreeNode* current = root;
        while (current != nullptr) {
            if (name == current->data.name) {
                std::cout << "Name: " << current->data.name << ", Birthday: " << current->data.birthday << std::endl;
                return;
            } else if (name < current->data.name) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        std::cout << "Person with name '" << name << "' not found." << std::endl;
    }

    void displayAllEntries() {
        displayEntries(root);
    }

    void displayBirthdaysByMonth(const std::string& month) {
        displayMonthEntries(root, month);
    }
};

int main() {
    Dictionary dictionary;


    dictionary.addEntry(Person("Chris", "12/15/1992"));
    dictionary.addEntry(Person("Shohei", "05/02/2021"));
    dictionary.addEntry(Person("Will", "09/10/1985"));


    std::cout << "All Entries:" << std::endl;
    dictionary.displayAllEntries();
    std::cout << std::endl;

    std::cout << "Search Result for Chris:" << std::endl;
    dictionary.searchByName("Chris");
    std::cout << std::endl;

    
    std::cout << "Removing Chris:" << std::endl;
    dictionary.removeEntry("Chris");
    std::cout << std::endl;

    std::cout << "All Entries:" << std::endl;
    dictionary.displayAllEntries();
    std::cout << std::endl;

    
    std::cout <<"Adding Two More Entries:" << std::endl;
    std::cout << "Tesco and Freddie" << std::endl;
    std::cout << std::endl;
        
    dictionary.addEntry(Person("Tesco", "05/05/2000"));

    dictionary.addEntry(Person("Freddie", "01/19/1949"));
    
    std::cout << "All Entries After Removal and Addtion of New :"      << std::endl;
    dictionary.displayAllEntries();
    std::cout << std::endl;
    
    
    return 0;
}
/*
All Entries:
Name: Chris, Birthday: 12/15/1992
Name: Shohei, Birthday: 05/02/2021
Name: Will, Birthday: 09/10/1985

Search Result for Chris:
Name: Chris, Birthday: 12/15/1992

Removing Chris:

All Entries:
Name: Shohei, Birthday: 05/02/2021
Name: Will, Birthday: 09/10/1985

Adding Two More Entries:
Tesco and Freddie

All Entries After Removal and Addtion of New :
Name: Freddie, Birthday: 01/19/1949
Name: Shohei, Birthday: 05/02/2021
Name: Tesco, Birthday: 05/05/2000
Name: Will, Birthday: 09/10/1985

*/