/*
 * @file      SequencesOptimizerTest.cpp
 * @brief     SequencesOptimizerTest is a test file to OptimizerOfSequence class.
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

#include <mili/mili.h>
#include <biopp/biopp.h>
#include <biopp-filer/bioppFiler.h>
#include <gtest/gtest.h>
#define GENE_DESIGN_H
#include "acuoso/GeneDesign.h"
#undef GENE_DESIGN_H
#include "acuoso/ICodonUsageModifier.h" 
#include "acuoso/SequencesOptimizer.h"

using namespace acuoso;

ICodonUsageModifier* getDerivedHumanizerBackend(const std::string& derivedKey);

TEST(SequencesOptimizerTest, DefualtConstructor)
{
    SequencesOptimizer opt;
    ASSERT_TRUE(opt._specificOptimizer != NULL);
}

static const size_t HUMAN = 3;
TEST(SequencesOptimizerTest, ParameterizedConstructor)
{
	ICodonUsageModifier* optimizer = getDerivedHumanizerBackend("GeneDesign");
    ASSERT_TRUE(optimizer != NULL);
    SequencesOptimizer opt(optimizer, ICodonUsageModifier::Organism(HUMAN));
    ASSERT_TRUE(opt._specificOptimizer != NULL);    
}

static const size_t FIRST_SEQUENCE = 3;
static const size_t SECOND_SEQUENCE = 5;

TEST(SequencesOptimizerTest, OptimizerMethod)
{
    //------------------------------- create file with 2 sequence in format fasta --------------------------
    const std::string inputFile = "/tmp/acuoso-fileTest.fasta";
    const std::string descriptionSequence1 = ">YAR053W";                                             
    const std::string descriptionSequence2 = ">YAR029W"; 
    std::ofstream file(inputFile.c_str());
    file << descriptionSequence1 << " \n";   
    file << "ATGTATGAGTACTTATTATTAACGAGGAAAAATGCCCTATTTTCTTTAGCAATTAATGAACCATCG"
            "CCAACTTTTGCTTTAACAATTATTGCCATTTTCAGCAGTACTAACGTAA\n";   
	file << descriptionSequence2 <<" \n";   
    file << "ATGAATAAATATCTATTTGACCATAAAATATGGAGTACTCCTTACTACTTTTATTGCGAAGAAGAT"
            "TGCCACCGTCTTTTTCTAAGTTTTATTGAGGGAAGAACTTTCGAGAAGCCAACAAGCAACGCTGAG"
            "GAAAATGTACAGGAGACTGAAGCTGGCGAATCTTTCACATTAAATCCCGGAGAAGATTTTCAAAAT"
            "TGCTTTCCAAGACAGCGGATATTGTAA \n";   
    file.close();

	//------------------------------------ optimizer all sequence ------------------------------------------
    SequencesOptimizer optimizerSequenceOfFile; //using geneDesign to default   
    optimizerSequenceOfFile.optimizer(inputFile.c_str());

   //------------------------------------ check output -----------------------------------------------------
	    
    std::ifstream outputFile(optimizerSequenceOfFile._outputFileName.c_str());
    ASSERT_TRUE(outputFile);

    std::string aux;
    std::string description1;
    std::string seq1;
    getline(outputFile, description1);
    for(int i = 0; i < FIRST_SEQUENCE; ++i)
    {
    	getline(outputFile, seq1);
    	aux += seq1;
    }
    seq1 = aux;
    aux.clear();
	std::string description2;
    std::string seq2;
    getline(outputFile, description2);
    for(int i = 0; i < SECOND_SEQUENCE; ++i)
    {
    	getline(outputFile, seq2);
    	aux += seq2;
    }
    seq2 = aux;    
    const std::string seq1Expected = "AUGUACGAGUACCUGCUGCUGACCCGCAAGAACGCCCUGUUCAGCCUGGCCAUCAACGAGCCCAGCCCCACCUUCGCCCUGACCAUCAUCGCCAUCUUCAGCAGCACCAACGUG"; 
    const std::string seq2Expected = "AUGAACAAGUACCUGUUCGACCACAAGAUCUGGAGCACCCCCUACUACUUCUACUGCGAGGAGGACUGCCACCGCCUGUUCCUGAGCUUCAUCGAGGGCC"
									 "GCACCUUCGAGAAGCCCACCAGCAACGCCGAGGAGAACGUGCAGGAGACCGAGGCCGGCGAGAGCUUCACCCUGAACCCCGGCGAGGACUUCCAGAACUG"
								  	 "CUUCCCCCGCCAGCGCAUCCUGUGA";
    EXPECT_EQ(description1, descriptionSequence1);
	EXPECT_EQ(seq1Expected, seq1);
    EXPECT_EQ(description2, descriptionSequence2);
    EXPECT_EQ(seq2Expected, seq2);

	mili::assert_throw<UnlinkException>(unlink(inputFile.c_str()) == 0);
 	mili::assert_throw<UnlinkException>(unlink(optimizerSequenceOfFile._outputFileName.c_str()) == 0);     
}