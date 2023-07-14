/* Description
 *
 * @authors Mohd Suhail
 * @date    2023-07-07 14:39:07
 */

#pragma once
#include <fstream>
#include <string>
#include <stdexcept>
#include <json/json.h>
#include <mutex>

template <typename T>
class FileHandler
{
public:
    FileHandler() = delete;
    FileHandler(const FileHandler &) = delete;

    explicit FileHandler(const std::string &filename) : filename(filename) {}

    virtual void readFile(T &content) = 0;
    virtual void writeFile(const T &t) = 0;
    virtual void overWriteFile(const T &content) = 0;
    virtual void clear()
    {
        std::lock_guard<std::mutex> lock(m_lock);
        std::ofstream file(filename, std::ofstream::trunc);
        if (!file)
        {
            throw std::runtime_error("Failed to open the file for clearing " + filename);
        }
        file.close();
    }
    virtual void deleteFile()
    {
        std::lock_guard<std::mutex> lock(m_lock);
        if (remove(filename.c_str()) != 0)
        {
            throw std::runtime_error("Failed to delete the file " + filename);
        }
    }
    virtual ~FileHandler() {}

protected:
    std::string filename;
    std::mutex m_lock;
};

class TextFileHandler : public FileHandler<std::string>
{
public:
    using FileHandler::FileHandler;
    typedef std::shared_ptr<TextFileHandler> TextFileHandlerSPtrType;
    typedef std::unique_ptr<TextFileHandler> TextFileHandlerUPtrType;

    void readFile(std::string &content) override
    {
        std::lock_guard<std::mutex> lock(m_lock);

        std::ifstream file(filename);
        if (!file)
        {
            throw std::runtime_error("Failed to open the file " + filename);
        }

        std::string line;
        while (std::getline(file, line))
        {
            content += line + "\n";
        }

        file.close();
    }

    void writeFile(const std::string &content) override
    {
        std::lock_guard<std::mutex> lock(m_lock);
        std::ofstream file(filename, std::ios::app);
        if (!file)
        {
            throw std::runtime_error("Failed to create the file for writing " + filename);
        }

        file << content << std::endl;

        file.close();
    }

    void overWriteFile(const std::string &content) override
    {
        std::lock_guard<std::mutex> lock(m_lock);
        std::ofstream file(filename, std::ios::trunc);
        if (!file)
        {
            throw std::runtime_error("Failed to create the file for appending " + filename);
        }

        file << content << std::endl;

        file.close();
    }
};

class JsonFileHandler : public FileHandler<Json::Value>
{

public:
    using FileHandler::FileHandler;
    typedef std::shared_ptr<JsonFileHandler> JsonFileHandlerSPtrType;
    typedef std::unique_ptr<JsonFileHandler> JsonFileHandlerUPtrType;

    void readFile(Json::Value &content) override
    {
        std::lock_guard<std::mutex> lock(m_lock);
        std::ifstream file(filename, std::ifstream::binary);
        if (!file)
        {
            throw std::runtime_error("Failed to open the file " + filename);
        }

        file >> content;
        file.close();
    }

    void writeFile(const Json::Value &content) override
    {
        throw std::runtime_error("Use overWriteFile method, append write is not feasable in a json file : If you need to append, readFile first then use overwriteFile method to make sure json format is intact");
    }

    void overWriteFile(const Json::Value &content) override
    {
        std::lock_guard<std::mutex> lock(m_lock);
        std::ofstream file(filename, std::ios::trunc);
        if (!file)
        {
            throw std::runtime_error("Failed to create the file for appending " + filename);
        }

        file << content << std::endl;

        file.close();
    }
};