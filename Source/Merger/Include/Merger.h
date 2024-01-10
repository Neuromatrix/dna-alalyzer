#include <string>
#include <set>
#include <vector>
#include <unordered_map>
#include <stdexcept>
namespace Server::Merger
{
    std::string Merge(const std::vector<std::string> &Data){
        std::string result;
        for (const auto & element : Data) {
            result.append(element);
        }
        return result;
    }

}
