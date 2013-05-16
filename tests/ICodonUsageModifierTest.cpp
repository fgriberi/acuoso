/*
 * @file      ICodonUsageModifierTest.cpp
 * @brief     ICodonUsageModifierTest is a test file to GeneDesign backend.
 *
 * @author    Franco Riberi
 * @email     fgriberi AT gmail.com
 *
 * Contents:  Source file.
 *
 * System:    acuoso: Abstract Codon Usage Optimization Software for Organisms 
 * Language:  C++
 *
 * @date May 2013
 *
 * Copyright (C) 2013 Franco Riberi, FuDePAN
 *
 * This file is part of acuoso.
 *
 * acuoso is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * acuoso is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with acuoso. If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <string>
#include <fstream>
#include <biopp/biopp.h>
#include <acuoso/acuoso.h>
#include <gtest/gtest.h>

using namespace acuoso;

/// Temporal functions
int linkFictitious();    

TEST(GeneDesignBackendTestSuite, BasicTest)
{
    linkFictitious();    
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

    const std::string expectedResult = "UUCAAGACCGCCUGCGGCCUGUUCCCCCCCACCGGCGCCACCGGCCGCUGACACACC"
                                       "GGCAUCACCGUGCCCCUGUGCGCCUGCUUCAUCACCCCCCCCCGCGUGAACCUGCGC"
                                       "AGCAACGCCCCCCUGGUGAACAGCCGCUGCGACACCCCCGUGACCAGCUGACCCAGC"
                                       "ACCAGCGUGAGCCCCGACUGAGUGAGCAUCGGCUGCAGCCGCGGCUGACGCCGCAAG"
                                       "CGCAGCCUGCCCGGCCAGCUGCUGCGCGAGGCCUGAUGACACCACGAGGGCUGCCGC"
                                       "GUGUUCCGCAGCGCCCUGCCCCUGUGCCGCAGCGGCCGCUGAGUGACCGCCUUCCUG"
                                       "ACCGGCGACCGCGGCGGCCGCUGCGCCGGCGGCCUGCCCAUGGGCCAGCCCAUCGGC"
                                       "CGCAGCAACGCCGACAUGGUGCGCCGCGUGUACUGAGCCAGCUGGUGAAGCAGCGGC"
                                       "CCCUGAAUGCGCCUGAUCCCCACCGCCGAGCACGCCCCCAGCAACCAGGGCGCCGCC"
                                       "UGCCGCAACGGCCAGCUGUGCAGCGGCACCGACUACUUCGGCUGCCCCUGCUUCUUC"
                                       "CUGUUCCUGUACUGGCUGCUGAUGGUGACCAUCGAGCGCCUGCUGCCCUACAGCUAC"
                                       "UGGAUCGGCCACCCCGUGAGCAACCGCGCCAUCGUGUACCUGUUCACCGGCUUCAUC"
                                       "CCCCUGAACUACAAGGAGGUGAAGACCCUGCACCUGAUCCUGCUGUUCAACACCACC"
                                       "AAGUGGGAGCUGAAGUGCCAGCACCGCAAGCUGGAGCUG"; 

    ASSERT_EQ(seqDest.getString(), expectedResult);
}