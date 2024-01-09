#include "Analyzer.h"

namespace Server::Analyzer
{
    Analyzer::Analyzer(const std::string &data)
    {
        this->sequence = data;
        Update();
    }

    const double Analyzer::CalculateGCContent()
    {
        int gcCount = 0;
        for (char nucleotide : this->sequence)
        {
            if (nucleotide == 'G' || nucleotide == 'C')
            {
                gcCount++;
            }
        }

        double gcContent = static_cast<double>(gcCount) / this->sequence.length() * 100.0;
        return gcContent;
    }

    const std::unordered_map<std::string, int> Analyzer::CalculateCodonUsage()
    {
        std::unordered_map<std::string, int> codonCounts;

        for (int i = 0; i < this->sequence.length() - 2; i += 3)
        {
            std::string codon = this->sequence.substr(i, 3);
            codonCounts[codon]++;
        }

        return codonCounts;
    }

    const std::vector<std::string> Analyzer::FindORFs()
    {
        std::vector<std::string> orfs;
        size_t start = this->sequence.find("ATG");

        while (start != std::string::npos)
        {
            size_t stop = this->sequence.find_first_of("TGA", start + 3);
            if (stop != std::string::npos && (stop - start) % 3 == 0)
            {
                std::string orf = this->sequence.substr(start, stop - start + 3);
                orfs.push_back(orf);
            }
            start = this->sequence.find("ATG", start + 1);
        }

        return orfs;
    }

    void Analyzer::SetSequence(const std::string &data)
    {
        this->sequence = data;
        Update();
    }

    const std::string Analyzer::GetSequence()
    {
        return this->sequence;
    }

}
