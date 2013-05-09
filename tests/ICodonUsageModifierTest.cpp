/*
    Copyright (C) 2012 Franco Riberi, FuDePAN

    This file is part of the Fideo Library.

    Fideo is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Fideo is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Fideo.  If not, see <http://www.gnu.org/licenses/>.

    This is a test file.
*/
#include <string>
#include <fstream>
#include <fideo/fideo.h>
#include <biopp/biopp.h>
#include <acuoso/acuoso.h>
#include <gtest/gtest.h>

using namespace acuoso;

TEST(GeneDesignBackendTestSuite, BasicTest)
{
    const std::string sequence = "UUUAAAACAGCCUGUGGGUUGUUCCCACCCACAGGCGCCACCGGGCGUUAGCACACUGGU"
	     	                         "AUCACGGUACCCUUGUGCGCCUGUUUUAUAACCCCACCCCGAGUAAACCUUAGAAGCAAU"
             		                 "GCACCUCUGGUCAAUAGUAGGUGUGACACACCAGUCACAUCGUGACCAAGCACUUCUGUC"
                      			     "UCCCCGGACUGAGUAUCAAUAGGCUGCUCGCGCGGCUGAAGGAGAAAGCGUUCGUUACCC"
	                               "GGCCAGCUACUUCGAGAAGCCUAGUAACACCAUGAAGGUUGCAGAGUGUUUCGCUCAGCA"
       		                       "CUUCCCCUGUGUAGAUCAGGCCGAUGAGUCACCGCGUUCCUCACGGGCGACCGUGGCGGU"
               		               "CGCUGCGCUGGUGGCCUGCCUAUGGGGCAACCCAUAGGACGCUCUAAUGCUGACAUGGUG"
                      	     		 "CGAAGAGUCUAUUGAGCUAGCUGGUAGUCCUCCGGCCCCUGAAUGCGGCUAAUCCCAACU"
                      	 	     	 "GCGGAGCACGCACCCUCAAACCAGGGGGCAGCGUGUCGUAACGGGCAACUCUGCAGCGGA"
                      	   	 	   "ACCGACUACUUUGGGUGUCCGUGUUUCUUUUUAUUCCUAUAUUGGCUGCUUAUGGUGACA"
                      		       "AUUGAGAGAUUGUUACCAUAUAGCUAUUGGAUUGGCCAUCCGGUGAGCAACAGAGCUAUU"
                     		         "GUGUAUCUGUUUACUGGUUUCAUACCCCUUAAUUACAAAGAAGUCAAAACCCUUCACUUG"
                          		   "AUCUUGUUAUUCAAUACAACAAAAUGGGAGCUCAAGUGUCAACACAGAAAACUGGAGCUC";
    
    const biopp::NucSequence auxSeq(sequence);
  	biopp::AminoSequence aminoSeq;
	  auxSeq.translate(aminoSeq); 
    biopp::NucSequence seqDest;

    ICodonUsageModifier* humanizer = mili::FactoryRegistry<ICodonUsageModifier, std::string>::new_class("GeneDesign");
    ASSERT_TRUE(humanizer != NULL);

    humanizer->setOrganism(acuoso::ICodonUsageModifier::Organism(3));
    EXPECT_NO_THROW(humanizer->changeCodonUsage(aminoSeq, seqDest));
    delete humanizer;

    const std::string expectedResult = "ATGCGCCTGATCCCCACCGCCGAGCACGCCCCCAGCAACCAGGGCGCCGCCTGCCGCAACGGCCAGCTGTGCAGCGGCAC"
                                       "CGACTACTTCGGCTGCCCCTGCTTCTTCCTGTTCCTGTACTGGCTGCTGATGGTGACCATCGAGCGCCTGCTGCCCTACA"
                                       "GCTACTGGATCGGCCACCCCGTGAGCAACCGCGCCATCGTGTACCTGTTCACCGGCTTCATCCCCCTGAACTACAAGGAG"
                                       "GTGAAGACCCTGCACCTGATCCTGCTGTTCAACACCACCAAGTGGGAGCTGAAGTGCCAGCACCGCAAGCTGGAGCTG";
    ASSERT_EQ(seqDest.getString(), expectedResult);
}

// TEST(GeneDesignBackendTestSuite, BasicTest2)
// {
//     const std::string sequence = "GCUGUGUGUUGUGUGUGCCAUGGAUCAGUCAAACACAUUAUAGGCUUGUACAGCAGGAUG"
//                                  "AGUACACCAGCGCUGGUUACGUGACGUGUUGGUAUCAGACUGGUAUGAUUGUCCCACCAG"
//                                  "GAACCCCAAAUUCUAGCUCUAUUAUGUGCUUUGCAUCAGCGUGCAACGACUUCUCAGUAA"
//                                  "GAAUGUUGAGGGACACACCAUUCAUAUCCCAGGAUAAUAAGCUGCAAGGGGAUGUGGAAG"
//                                  "AAGCCAUUGAGAGGGCACGUUGUACAGUUGCUGACACCAUGCGUACGGGGCCUAGCAAUU"
//                                  "CCGCGAGCGUACCUGCACUCACUGCAGUUGAGACAGGGCACACCUCGCAAGUUACUCCAA"
//                                  "GUGACACUAUGCAGACAAGACAUGUGAAAAACUAUCAUUCGCGCUCUGAGUCGACUGUGG";
    
//     const biopp::NucSequence auxSeq(sequence);
//     biopp::AminoSequence aminoSeq;
//     auxSeq.translate(aminoSeq); 
//     biopp::NucSequence seqDest;

//     acuoso::ICodonUsageModifier* humanizer = mili::FactoryRegistry<acuoso::ICodonUsageModifier, std::string>::new_class("GeneDesign");
//     ASSERT_TRUE(humanizer != NULL);

//     EXPECT_NO_THROW(humanizer->changeCodonUsage(aminoSeq, seqDest));
//     delete humanizer;

//     const std::string expectedResult = "GGCACCCACCACAGCTACCCCCGCATCATCAGCTGCAAGGGCATGTGGAAGAAGCCCCTGCGCGGCCACGTGGTGCAGCT"
//                                        "GCTGACCCCCTGCGTGCGCGGCCTGGCCATCCCCCGCGCCTACCTGCACAGCCTGCAGCTGCGCCAGGGCACCCCCCGCA"
//                                        "AGCTGCTGCAGGTGACCCTGTGCCGCCAGGACATG";
//     ASSERT_EQ(seqDest.getString(), expectedResult);
// }