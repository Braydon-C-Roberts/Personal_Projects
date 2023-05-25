
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cstdio>
#include <string>
#include <windows.h>

std::map<std::string, std::pair<int, std::string>> inventory;
std::string fileName = "inventory.csv";

void menu();
void addItem();
void displayInventory();
void removeItem();
void loadInventory();
void saveInventory();
void resetInventory();

int main()
{
    std::cout << "Welcome to the food inventory system!!!\n\n";
    
    menu();

    return 0;
}

void menu()
{
    int option = 0;

    while (option != 7)
    {
        std::cout << "Please select an option below" << std::endl;
        std::cout << "1. Add an item of food" << std::endl;
        std::cout << "2. Remove an item of food" << std::endl;
        std::cout << "3. View inventory" << std::endl;
        std::cout << "4. Reset inventory" << std::endl;
        std::cout << "5. Load Inventory" << std::endl;
        std::cout << "6. Save Inventory" << std::endl;
        std::cout << "7. Exit program" << std::endl;
        std::cout << "Enter the number of your choice: ";
        std::cin >> option;
        std::cout << std::endl;

        if (option == 1)
        {
            addItem();
        }

        if (option == 2)
        {
            removeItem();
        }

        if (option == 3)
        {
            displayInventory();
        }
        if (option == 4)
        {
            resetInventory();
        }
        if (option == 5)
        {
            loadInventory();
        }
        if (option == 6)
        {
            saveInventory();
        }
    }
}

void addItem()
{
    std::string item;
    int quantity;
    std::string expDate;

    std::cout << "Enter the item you would like to add: ";
    getline(std::cin, item);
    std::cout << "Enter the quantity of that item to add: ";
    std::cin >> quantity;
    std::cout << "Enter the expiration date of the item (mm/dd/yy): ";
    std::cin >> expDate;

    inventory[item] = make_pair(quantity, expDate);
    std::cout << std::endl;
}

void removeItem()
{
    std::string itemToRemove;

    std::cout << "Enter the item that you would like to remove: ";
    std::cin >> itemToRemove;

    auto match = inventory.find(itemToRemove);
    if (match != inventory.end())
    {
        inventory.erase(match);
    }
    else
    {
        std::cout << "Item not found in inventory" << std::endl;
    }
    std::cout << "Item succesfully removed" << std::endl;
    std::cout << std::endl;
}

void displayInventory()
{
    for (const auto& pair : inventory)
    {
        const std::string& item = pair.first;
        int quantity = pair.second.first;
        const std::string& expDate = pair.second.second;

        std::cout << item << ", " << quantity << ", Expires on " << expDate << std::endl;
        std::cout << std::endl;
    }
}

void loadInventory()
{
    std::ifstream inputFile(fileName);
    if (!inputFile)
    {
        std::cout << "Inventory file not found. Creating a new file." << std::endl;
        std::ofstream createFile(fileName);
        if (!createFile)
        {
            std::cout << "Failed to create the inventory file: " << fileName << std::endl;
            return;
        }
        createFile.close();
    }

    if (!inputFile.is_open())
    {
        std::cout << "Failed to open the file: " << fileName << std::endl;
        return;
    }

    if (!inputFile)
    {
        std::cout << "Failded to open the file: " << fileName << std::endl;
        return;
    }

    inventory.clear();

    std::string line;
    while (getline(inputFile, line))
    {
        std::istringstream iss(line);
        std::string key, value1, value2;
        if (getline(iss, key, ',') && getline(iss, value1, ',') && getline(iss, value2))
        {
            int intValue;
            std::stringstream ss(value1);
            if (!(ss >> intValue))
            {
                std::cout << "Failed to convert value to int: " << value1 << std::endl;
                continue;
            }

            inventory[key] = make_pair(intValue, value2);
        }
    }
    std::cout << "Inventory succesfully loaded" << std::endl;
    std::cout << std::endl;
}

void saveInventory()
{
    std::ofstream outputFile(fileName);
    if (!outputFile)
    {
        std::cout << "Inventory file not found. Creating a new file." << std::endl;
        outputFile.open(fileName);
        if (!outputFile)
        {
            std::cout << "Failed to create the inventory file: " << fileName << std::endl;
            return;
        }
    }

    for (const auto& pair : inventory)
    {
        const std::string& key = pair.first;
        const auto& itemPair = pair.second;

        outputFile << key << "," << itemPair.first << "," << itemPair.second << "\n";
    }

    outputFile.close();
    std::cout << "Inventory succesfully saved" << std::endl;
    std::cout << std::endl;
}

void resetInventory()
{
    std::string option;

    std::cout << "If you are certain you would like to reset the inventory file pleas type RESET (case sensitive): ";
    std::cin >> option;
    std::cout << std::endl;

    if (option == "RESET")
    {
        if (remove(fileName.c_str()) == 0)
        {
            std::cout << "File deleted Successfully." << std::endl;
        }
        else
        {
            std::cout << "Failed to delete the file." << std::endl;
        }
    }
    std::cout << std::endl;
}