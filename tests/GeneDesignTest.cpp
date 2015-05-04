/*
 * @file      GeneDesignTest.cpp
 * @brief     GeneDesignTest is a test file to GeneDesign backend.
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

#define private public

#include <memory>
#include <biopp/biopp.h>
#include <acuoso/acuoso.h>
#include <etilico/etilico.h>
#include <gtest/gtest.h>
#define GENE_DESIGN_H
#include "acuoso/GeneDesign.h"
#undef GENE_DESIGN_H
#include "acuoso/ICodonUsageModifier.h"

using namespace acuoso;

ICodonUsageModifier* getDerivedHumanizerBackend(const std::string& derivedKey);

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

    ICodonUsageModifier* const humanizer = getDerivedHumanizerBackend("GeneDesign");
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

TEST(GeneDesignBackendTestSuite, InvalidBackend)
{
    EXPECT_THROW(ICodonUsageModifier* humanizer = getDerivedHumanizerBackend("Genedesign"), InvalidDerived);
}

TEST(GeneDesignBackendTestSuite, InvalidOrganism)
{
    GeneDesign geneDesign;
    geneDesign.setOrganism(ICodonUsageModifier::Organism(8)); //invalid organism
    const std::string fileName = "obsoletFileName.fasta";
    etilico::Command cmd;
    EXPECT_THROW(geneDesign.generateCommand(fileName, cmd), OrganismNotSupported);
}

TEST(GeneDesignBackendTestSuite, invalidPath)
{
    std::stringstream pathFile;
    pathFile << "tmp/acuoso-Jrkkxc_gdRT_3.FASTA";
    std::string fileName;
    GeneDesign geneDesign;
    EXPECT_THROW(geneDesign.getFileOutput(pathFile, fileName), IndexOutOfRange);
}

TEST(GeneDesignBackendTestSuite, CorrectCommand)
{
    GeneDesign geneDesign;
    geneDesign.setOrganism(ICodonUsageModifier::Organism(3));
    const std::string fileName = "/tmp/acuoso-uvkcIs";
    etilico::Command cmd;
    geneDesign.generateCommand(fileName, cmd);
    const etilico::Command expectdCmd = "perl Reverse_Translate.pl -i /tmp/acuoso-uvkcIs -o 3";
    EXPECT_EQ(cmd, expectdCmd);
}

static const size_t INVALID_COMMAND = 2;
TEST(GeneDesignBackendTestSuite, IncorrectCommand)
{
    etilico::Command cmd = "perl Reverse_Translate.pl -i tmp/acuoso-uvkcIs -o3";
    EXPECT_EQ(etilico::runCommand(cmd), INVALID_COMMAND);
}