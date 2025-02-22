/*!
 *  Copyright (c) 2024 by Contributors
 * \file xgrammar/pybind/python_methods.h
 * \brief The header for the support of grammar-guided generation.
 */

#ifndef XGRAMMAR_PYBIND_PYTHON_METHODS_H_
#define XGRAMMAR_PYBIND_PYTHON_METHODS_H_

#include <pybind11/pybind11.h>
#include <torch/extension.h>
#include <xgrammar/xgrammar.h>

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace xgrammar {

BNFGrammar BNFGrammar_InitNoNormalization(
    const std::string& ebnf_string, const std::string& root_rule
);

TokenizerInfo TokenizerInfo_Init(
    const std::vector<std::string>& encoded_vocab,
    std::string vocab_type,
    bool prepend_space_in_tokenization
);

std::string TokenizerInfo_GetVocabType(const TokenizerInfo& tokenizer);

std::vector<pybind11::bytes> TokenizerInfo_GetDecodedVocab(TokenizerInfo& tokenizer);

void GrammarMatcher_FillNextTokenBitmask(
    GrammarMatcher& matcher, torch::Tensor token_bitmask, int batch_id
);

std::vector<int> GrammarMatcher_DebugGetMaskedTokensFromBitmask(
    GrammarMatcher& matcher, torch::Tensor token_bitmask, int batch_id
);

#ifdef XGRAMMAR_BUILD_KERNELS
void GrammarMatcher_ApplyTokenBitmaskInplace(torch::Tensor logits, torch::Tensor token_bitmask);
#endif

}  // namespace xgrammar

#endif  // XGRAMMAR_PYBIND_PYTHON_METHODS_H_
