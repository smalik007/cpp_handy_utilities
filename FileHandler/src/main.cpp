#include <iostream>
#include <string>
#include <json/json.h>

#include "FileHandler.hpp"

using namespace std;

void demonstrateStringFileHandler()
{
    try
    {

        const string filename = "string_file.txt";
        string read_data;
        StringFileHandler string_file_obj(filename);

        /* This should thow an exception as we are reading a file before it's creation */
        // string_file_obj.readFile(read_data);
        // cout << "Step 1 : Reading file content" << endl;
        // cout << read_data << endl;

        string_file_obj.clear();
        string_file_obj.writeFile("Writing some random string");
        string_file_obj.readFile(read_data);
        cout << "Step 1 : Reading file content" << endl;
        cout << read_data << endl;

        /* Appending in file */
        read_data.clear();
        string_file_obj.writeFile("Appending some more info");
        string_file_obj.readFile(read_data);
        cout << "Step 2: Reading file content" << endl;
        cout << read_data << endl;

        /* Overwriting content in file */
        read_data.clear();
        string_file_obj.overWriteFile("Overwriting the content");
        string_file_obj.readFile(read_data);
        cout << "Step 3: Reading file content" << endl;
        cout << read_data << endl;

        /* Deleting the file */
        // string_file_obj.deleteFile();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

void demonstrateJsonFileHandler()
{
    try
    {

        const string filename = "json_file.json";
        Json::Value read_data;
        Json::Value write_data;
        JsonFileHandler json_file_obj(filename);

        /* This should thow an exception as we are reading a file before it's creation */
        // json_file_obj.readFile(read_data);
        // cout << "Step 1 : Reading file content" << endl;
        // cout << read_data << endl;

        /* Create a in valid json file and re run again the step 1, It should throw and invalid json file exception */

        json_file_obj.clear();
        write_data["name"] = "John";
        write_data["age"] = 23;
        write_data["city"] = "New york";
        write_data["is_employed"] = true;

        /* This should also throw an exception as appending to a file to json could mess up the json file format */
        // cout << "Step 2 : Reading file content" << endl;
        // json_file_obj.writeFile(write_data);

        // /* Overwriting content in file */
        read_data.clear();
        cout << "Step 3: Reading file content" << endl;
        json_file_obj.overWriteFile(write_data);
        json_file_obj.readFile(read_data);
        cout << read_data.toStyledString() << endl;

        read_data.clear();
        write_data.clear();
        write_data["name"] = "Peter";
        write_data["age"] = 25;
        write_data["city"] = "Texas";
        write_data["is_employed"] = false;

        cout << "Step 4: Reading file content" << endl;
        json_file_obj.overWriteFile(write_data);
        json_file_obj.readFile(read_data);
        cout << read_data.toStyledString() << endl;

        /* Deleting the file */
        // json_file_obj.deleteFile();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main()
{
    // demonstrateStringFileHandler();
    demonstrateJsonFileHandler();

    return 0;
}