//----------------------------------------------------------------------------
//  Project: Jurasic
//  OWL NExt
//  All rights reserved 1999
//
//  SUBSYSTEM:    Jurasic Application
//  FILE:         lang.cpp
//  AUTHOR:       Yura Bidus
//
//  OVERVIEW
//  ~~~~~~~~
//  Source file for implementation of TParserSelector (GENERIC).
//  (Generated by OWL 6.0 Class Expert for VC version 1.5)
//----------------------------------------------------------------------------
#include <coolprj/pch.h>
#pragma hdrstop

#include <coolprj/cooledit.h>
#include <coolprj/fpattern.h>

#include <coolprj/lang.h>

using namespace owl;
using namespace std;

struct TSyntaxParserInfo {
  LPCTSTR        pattern;
  TParserCreator func;
};

extern TSyntaxParser* AsmParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* BasicParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* BatchParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* CParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* DclParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* FortranParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* HtmlParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* ISParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* JavaParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* LispParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* PascalParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* PerlParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* PlainTextParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* PythonParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* RexxParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* RsrcParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* SgmlParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* ShParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* SiodParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* SqlParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* TclParserCreator(TCoolTextWnd* parent);
extern TSyntaxParser* TexParserCreator(TCoolTextWnd* parent);


TSyntaxParser* PlainTextParserCreator(TCoolTextWnd *parent)
{
  return new TPlainTextParser(parent);
}

TParserSelector::TParserInfo TParserSelector::ParserInfo [] = {
  { _T("*.asm;*.inc;*.s"),  (TParserCreator)AsmParserCreator, 0 },
  { _T("*.bas;*.vb;*.vbs;*.frm;*.dsm"),  (TParserCreator)BasicParserCreator, 0  },
  { _T("*.bat;*.btm;*.cmd"),  (TParserCreator)BatchParserCreator, 0  },
  { _T("*.cpp;*.cxx;*.cc"), (TParserCreator)CParserCreator, 0  },
  { _T("*.c"), (TParserCreator)CParserCreator, 0  },
  { _T("*.h;*.hpp;*.hxx;*.inl;*.tlh;*.tli"), (TParserCreator)CParserCreator, 0  },
  { _T("*.dcl;*.dcc"),  (TParserCreator)DclParserCreator, 0  },
  { _T("*.f;*.f90;*.f9p;*.fpp;*.for"),  (TParserCreator)FortranParserCreator, 0  },
  { _T("*.html;*.htm;*.shtml"),  (TParserCreator)HtmlParserCreator, 0  },
  { _T("*.rul"), (TParserCreator)ISParserCreator, 0  },
  { _T("*.java;*.jav;*.js"), (TParserCreator)JavaParserCreator, 0  },
  { _T("*.lsp"), (TParserCreator)LispParserCreator, 0  },
  { _T("*.pas"),  (TParserCreator)PascalParserCreator, 0  },
  { _T("*.pl"), (TParserCreator)PerlParserCreator, 0  },
  { _T("*.txt;*.doc;*.diz"),  (TParserCreator)PlainTextParserCreator, 0  },
  { _T("*.py"),  (TParserCreator)PythonParserCreator, 0  },
  { _T("*.rex;*.rexx;*.cmd"),  (TParserCreator)RexxParserCreator, 0  },
  { _T("*.rc;*.dlg"),  (TParserCreator)RsrcParserCreator, 0  },
  { _T("*.sgml"),  (TParserCreator)SgmlParserCreator, 0  },
  { _T("*.sh;*.conf"),  (TParserCreator)ShParserCreator, 0  },
  { _T("*.scm"),  (TParserCreator)SiodParserCreator, 0  },
  { _T("*.sql"),  (TParserCreator)SqlParserCreator, 0  },
  { _T("*.tcl"),  (TParserCreator)TclParserCreator, 0  },
  { _T("*.tex;*.sty;*.cls;*.clo;*.ltx;*.fd;*.dtx"),  (TParserCreator)TexParserCreator, 0  },
  { _T("*.*"),  (TParserCreator)PlainTextParserCreator, 0  }, // last any file
};

TParserSelector::TParserSelector(bool initDefTypes)
{
  if(initDefTypes){
    int count = COUNTOF(ParserInfo);
    for (int index = count-1; index >= 0; index--){
      Parsers.push_back(&ParserInfo[index]);
    }
  }
}
//
TParserSelector::~TParserSelector()
{
  for (int index = 0; index < (int)Parsers.size(); index++){
    if(Parsers[index]->Flags&pieDynamic){
      delete (LPTSTR)Parsers[index]->Pattern;
      delete Parsers[index];
    }
  }
}
//
bool TParserSelector::MatchFileType(LPCTSTR tplFilter, LPCTSTR path)
{
  // Make locale copy of filter
  //
  TAPointer<TCHAR> fltrCopy(nstrnewdup(tplFilter));
  LPTSTR fltr = fltrCopy;
  LPTSTR nxtFltr;

  // For each template, try each wilcard specified
  //
  while (fltr){
    // Is there another wildcard following - Null terminate at ';'
    //
    nxtFltr = _tcschr(fltr, _T(';'));
    if (nxtFltr)
      *nxtFltr++ = 0;
    if(fpattern_isvalid(fltr)){
      owl::tstring pattern;
      if(*fltr != _T('*'))
        pattern += _T('*');
      pattern += fltr;
      if(fpattern_matchn(pattern.c_str(), path))
        return true;
    }
    // Try next filter
    //
    fltr = (nxtFltr && *nxtFltr) ? nxtFltr : 0;
  }
  return false;
}
//
TParserSelector::TParserInfo*
TParserSelector::MatchParser(LPCTSTR filename)
{
  if (filename==0 || _tcsrchr(filename, _T('.'))==0)
    return 0;

  for (int index = Parsers.size()-1; index >= 0; index--){
    if(MatchFileType(Parsers[index]->Pattern, filename))
      return Parsers[index];
  }
  return 0;
}
//
TSyntaxParser*
TParserSelector::CreateParser(TCoolTextWnd* parent, LPCTSTR filename)
{
  TParserInfo* info = MatchParser(filename);
  if(!info)
    return PlainTextParserCreator(parent);
  return info->Func(parent);
}
//
void TParserSelector::AddParser(LPCTSTR pattern, TParserCreator func)
{
  TParserInfo* info = new TParserInfo;
  info->Pattern = nstrnewdup(pattern);
  info->Func    = func;
  info->Flags   = pieDynamic;

  Parsers.push_back(info);
}
//
//TSyntaxParser*
//ChooseSyntaxParser(TCoolTextWnd* parent, LPCTSTR filename)
//{
//  TParserSelector selector;
//  return selector.CreateParser(parent, filename);
//}
//