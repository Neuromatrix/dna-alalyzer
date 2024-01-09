#include <string>
#include <set>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
namespace Server::Analyzer
{
    class Analyzer
    {
    private:
        //*-----------NON STATIC VAR------------*//
        std::string sequence;
        uint32_t len;
        std::unordered_map<char, uint32_t> nucCount;

        //*---------------STATIC----------------*//
        std::string avNucleotides = "ATCG";


        void Update(){
            len = this->sequence.size();
            for (const auto &nuc : sequence)
            {
                if (avNucleotides.find(nuc) == std::string::npos)
                {
                    std::cout << nuc << std::endl;
                    throw std::invalid_argument("Wrong nucletides in seq!");
                }
                nucCount[nuc]++;
            }
        }
    public:


        /// @brief
        /// @param data
        void SetSequence(const std::string &data);

        /// @brief
        /// @return
        const std::string GetSequence();

        /// @brief
        /// @param dnaSequence
        /// @return
        const double CalculateGCContent();

        /// @brief
        /// @param dnaSequence
        /// @return
        const std::unordered_map<std::string, int> CalculateCodonUsage();

        /// @brief
        /// @param dnaSequence
        /// @return
        const std::vector<std::string> FindORFs();


        /// @brief
        /// @param data
        Analyzer(const std::string &data);

        ~Analyzer() {}
    };


}
