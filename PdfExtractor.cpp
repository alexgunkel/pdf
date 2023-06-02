#include "PdfExtractor.h"
#include <iostream>

#include <xpdf/GlobalParams.h>
#include <xpdf/PDFDoc.h>
#include <xpdf/TextOutputDev.h>
#include <sstream>

namespace {
    void printChars(void *stream, const char *text, int len)
    {
        auto buf = static_cast<std::stringbuf*>(stream);
        buf->sputn(text, len);
    }
}

struct PdfExtractor::config {
    TextOutputControl textOutputControl;
};

std::string PdfExtractor::parseFile(std::string_view fileName) const {
    std::stringbuf stringBuf{};
    auto doc = new PDFDoc(const_cast<char*>(fileName.data()), nullptr, nullptr, nullptr);
    if (!doc->isOk()) {
        throw PdfExtractor::NoValidPdf{"cannot read file"};
    }
    auto out = new TextOutputDev(printChars, &stringBuf, &_cfg->textOutputControl);

    doc->displayPages(out, 1, doc->getNumPages(), 72, 72, 0,
                      gFalse, gTrue, gFalse);

    return stringBuf.str();
}

PdfExtractor::PdfExtractor() {
    globalParams = new GlobalParams("");
    globalParams->setTextEncoding("UTF-8");
    UnicodeMap *uMap;

    // get mapping to output encoding
    if (!(uMap = globalParams->getTextEncoding())) {
        throw std::runtime_error{"Couldn't get text encoding"};
    }

    _cfg = std::make_unique<PdfExtractor::config>();
    _cfg->textOutputControl.clipText = gFalse;
    _cfg->textOutputControl.discardDiagonalText = gFalse;
    _cfg->textOutputControl.insertBOM = gFalse;
    _cfg->textOutputControl.marginLeft = 0;
    _cfg->textOutputControl.marginRight = 0;
    _cfg->textOutputControl.marginTop = 0;
    _cfg->textOutputControl.marginBottom = 0;
}

PdfExtractor::~PdfExtractor() = default;
