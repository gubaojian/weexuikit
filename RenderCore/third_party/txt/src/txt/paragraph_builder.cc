/*
 * Copyright 2017 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <list>
#include <cstdlib>
#include "paragraph_builder.h"
#include "paragraph_style.h"
#include "unicode/unistr.h"

namespace txt {

ParagraphBuilder::ParagraphBuilder(
    ParagraphStyle style,
    std::shared_ptr<FontCollection> font_collection)
    : font_collection_(std::move(font_collection)) {
  SetParagraphStyle(style);
}

ParagraphBuilder::~ParagraphBuilder() = default;

void ParagraphBuilder::SetParagraphStyle(const ParagraphStyle& style) {
  paragraph_style_ = style;
  paragraph_style_index_ = runs_.AddStyle(style.GetTextStyle());
  runs_.StartRun(paragraph_style_index_, text_.size());
}

void ParagraphBuilder::PushStyle(const TextStyle& style) {
  size_t style_index = runs_.AddStyle(style);
  style_stack_.push_back(style_index);
  runs_.StartRun(style_index, text_.size());
}

void ParagraphBuilder::Pop() {
  if (style_stack_.empty())
    return;
  style_stack_.pop_back();
  runs_.StartRun(PeekStyleIndex(), text_.size());
}

size_t ParagraphBuilder::PeekStyleIndex() const {
  return style_stack_.size() ? style_stack_.back() : paragraph_style_index_;
}

const TextStyle& ParagraphBuilder::PeekStyle() const {
  return runs_.GetStyle(PeekStyleIndex());
}

void ParagraphBuilder::AddText(const std::u16string& text) {
  text_.insert(text_.end(), text.begin(), text.end());
}

void ParagraphBuilder::AddText(const std::string& text) {
  auto icu_text = icu::UnicodeString::fromUTF8(text);
  std::u16string u16_text(icu_text.getBuffer(),
                          icu_text.getBuffer() + icu_text.length());
  AddText(u16_text);
}

inline std::u16string stringFromUTF8(const char* text){
  UErrorCode pErrorCode = U_ZERO_ERROR;
  int length = strlen(text) + 1;
  UChar *dest = (UChar *)std::malloc(sizeof(UChar)*strlen(text));
  int32_t destLength = 0;
  UChar* end = u_strFromUTF8(dest, length, &destLength, text,length, &pErrorCode);
  std::u16string u16_text(dest, dest + destLength);
  std::free(dest);
  return  u16_text;
}

void ParagraphBuilder::AddText(const char* text) {
  std::u16string u16_text = stringFromUTF8(text);
  AddText(u16_text);
}

std::unique_ptr<Paragraph> ParagraphBuilder::Build() {
  runs_.EndRunIfNeeded(text_.size());

  std::unique_ptr<Paragraph> paragraph = std::make_unique<Paragraph>();
  paragraph->SetText(std::move(text_), std::move(runs_));
  paragraph->SetParagraphStyle(paragraph_style_);
  paragraph->SetFontCollection(font_collection_);
  return paragraph;
}

}  // namespace txt
