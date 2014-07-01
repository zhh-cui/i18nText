// Copyright [2014] <cuizhaohui>
/**
 * \file i18nText.cpp
 * \author CUI Zhao-hui, zhh.cui@gmail.com
 * \date 2014-07-01
 */

#include "../include/i18nText.h"

i18nText::i18nText() {
    valid = false;
    size.val[0] = 25;
    size.val[1] = 0.5;
    size.val[2] = 0.1;

}

i18nText::~i18nText() {
    if (valid) {
        FT_Done_Face(face);
        FT_Done_FreeType(library);
    }
}

bool i18nText::setFont(const char *name) {
    if (name) {
        if (FT_Init_FreeType(&library))
            return false;
        if (FT_New_Face(library, name, 0, &face))
            return false;
    }
    FT_Set_Pixel_Sizes(face, (int)this->size.val[0], 0);
    valid = true;
    return true;
}

void i18nText::setSize(cv::Scalar *size) {
    if (size) {
        this->size.val[0] = fabs(size->val[0]);
        this->size.val[1] = fabs(size->val[1]);
        this->size.val[2] = fabs(size->val[2]);
    }
}

int i18nText::putText(cv::Mat &img, const wchar_t *text, cv::Point pos, cv::Scalar color) {
    if (img.rows <= 0 || img.cols <= 0 || !img.data)
        return -1;
    if (text == NULL || text[0] == L'\0')
        return 0;

    wint_t i;
    for (i = 0; text[i] != L'\0'; ++i) {
        putWChar(img, text[i], pos, color);
    }

    return (int)i;
}

void i18nText::putWChar(cv::Mat &img, wchar_t wc, cv::Point &pos, cv::Scalar color) {
    FT_UInt glyph_index = FT_Get_Char_Index(face, wc);
    FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
    FT_Render_Glyph(face->glyph, FT_RENDER_MODE_MONO);
    FT_GlyphSlot slot = face->glyph;

    int rows = slot->bitmap.rows;
    int cols = slot->bitmap.width;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int off  = ((0 == 0) ? i : (rows - 1 - i)) * slot->bitmap.pitch + j / 8;
            if (slot->bitmap.buffer[off] & (0xC0 >> (j % 8))) {
                int r = (0 == 0) ? pos.y - (rows - 1 - i) : pos.y + i;
                ;
                int c = pos.x + j;

                if (r >= 0 && r < img.rows && c >= 0 && c < img.cols) {
                    cv::Vec3b scalar = img.at<cv::Vec3b>(r, c);

                    for (int k = 0; k < 3; ++k) {
                        scalar.val[k] = color.val[k];
                    }

                    img.at<cv::Vec3b>(r, c) = scalar;
                }
            }
        }
    }

    double space = size.val[0] * size.val[1];
    double sep = size.val[0] * size.val[2];

    pos.x += (int)((cols ? cols : space) + sep);
}

