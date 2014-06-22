#include "stdafx.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include "CppUnitTest.h"

#include "Task.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;


std::string readWholeFile(const std::string &strFileName)
{
    std::ifstream ifs(strFileName.c_str(), std::ios::in );

    std::string content(std::istreambuf_iterator<char>(ifs), (std::istreambuf_iterator<char>()));

    return content;
}


namespace TestAppTest2
{		
    TEST_CLASS(UnitTest1)
    {
    public:
        // ===============================================================================        
        TEST_METHOD(Trivial1)
        {
            char *c = NULL;
            try {
                removeComments(c);
            } 
            catch (...)
            {
                Assert::Fail();
            }

            Assert::AreEqual(NULL, c);
        }

        TEST_METHOD(Trivial2)
        {
            char expected[1] = {'\0'};
            char c[] = "";
            removeComments(c);

            Assert::AreEqual('\0', *c);
            Assert::AreEqual(expected, c);
        }

        // ===============================================================================        
        TEST_METHOD(BaseCase1)
        {
            char workContent[] = "// this is the comment";
            char expectedContent[] = "";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(BaseCase2)
        {
            char workContent[] = "/* another comment */";
            char expectedContent[] = "";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(BaseCase3)
        {
            char workContent[] = "text // comment";
            char expectedContent[] = "text ";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(BaseCase4)
        {
            char workContent[]     = "text1 /* comment */ text2";
            char expectedContent[] = "text1  text2";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComplexCase1)
        {
            char workContent[] = " text1 /**/ text2 /* */ text3 /* comment */ text4";
            char expectedContent[] = " text1  text2  text3  text4";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComplexCase2)
        {
            char workContent[] = "/***  text    ***/";
            char expectedContent[] = "";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComplexCase3)
        {
            char workContent[] = "/**  text  **/";
            char expectedContent[] = "";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComplexCase4)
        {
            char workContent[] = "/**  text  **/ text";
            char expectedContent[] = " text";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComplexCase5)
        {
            char workContent[] =
                "int z1 = 6/3;\n"
                "int z2 = 10 / 5;";
            char expectedContent[] = 
                "int z1 = 6/3;\n"
                "int z2 = 10 / 5;";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(MultilineCase1)
        {
            char workContent[] = "  /*\n"
                "* /\n"
                "text1\n"
                "/*\n"
                "*/\n"
                "text2\n"
                "/*\n"
                "*/";

            char expectedContent[] = "  \n"
                "text2\n"
                "";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(MultilineCase2)
        {
            char workContent[] = 
                "  //\n"
                "// comment\n"
                "text1\n"
                "//\n"
                "//\n"
                "text2 // one more\n"
                "\n";

            char expectedContent[] = 
                "  \n"
                "\n"
                "text1\n"
                "\n"
                "\n"
                "text2 \n"
                "\n";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(MultilineCase3)
        {
            char workContent[] =
                "/* c comment // cpp comment\n"
                "int zz = 5;\n"
                "*/\n";

            char expectedContent[] =
                "\n";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(MultilineCase4)
        {
            char workContent[] =
                "// cpp comment /*  /*\n"
                "int zz = 5;";

            char expectedContent[] =
                "\n"
                "int zz = 5;";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(StringCase1)
        {
            char workContent[]     = "printf(\"this is a simple string\")";
            char expectedContent[] = "printf(\"this is a simple string\")";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(StringCase2)
        {
            char workContent[]     = "printf(\"this /* is a string with */ comment\")";
            char expectedContent[] = "printf(\"this /* is a string with */ comment\")";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(StringCase3)
        {
            char workContent[]     = "printf(\"this is a string with // comment\")";
            char expectedContent[] = "printf(\"this is a string with // comment\")";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(StringCase4)
        {
            char workContent[]     = "printf(\"this is /* a string */ with // comment\")";
            char expectedContent[] = "printf(\"this is /* a string */ with // comment\")";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(TrickyStringCase1)
        {
            char workContent[]     = "printf(\"this is \\\\/* \\\"a string\\\" */\\\\ with escaped chars\");";
            char expectedContent[] = "printf(\"this is \\\\/* \\\"a string\\\" */\\\\ with escaped chars\");";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(TrickyStringCase2)
        {
            char workContent[] = "printf(\"this is \\\\/* \\\"a tricky string */\\\\ with escaped chars\");";
            char expectedContent[] = "printf(\"this is \\\\/* \\\"a tricky string */\\\\ with escaped chars\");";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(TrickyStringCase3)
        {
            char workContent[]     = "printf(\"this is \\\\/* \\\"a string /*\\\" \\\\ with escaped */ chars\");";
            char expectedContent[] = "printf(\"this is \\\\/* \\\"a string /*\\\" \\\\ with escaped */ chars\");";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        // ===============================================================================        
        TEST_METHOD(ProcessingFiles1)
        {
            std::string workFileContent = readWholeFile("File01.c");
            std::string expectedFileContent = readWholeFile("FileRes01.c");

            Assert::IsTrue(!workFileContent.empty() && !expectedFileContent.empty());

            char *szFileContent = const_cast<char*>(workFileContent.c_str());
            removeComments(szFileContent);

            Assert::AreEqual(expectedFileContent.c_str(), szFileContent);
        }

        TEST_METHOD(ProcessingFiles2)
        {
            std::string workFileContent = readWholeFile("File02.c");
            std::string expectedFileContent = readWholeFile("FileRes02.c");

            Assert::IsTrue(!workFileContent.empty() && !expectedFileContent.empty());

            char *szFileContent = const_cast<char*>(workFileContent.c_str());
            removeComments(szFileContent);

            Assert::AreEqual(expectedFileContent.c_str(), szFileContent);
        }

        TEST_METHOD(ProcessingFiles3)
        {
            std::string workFileContent = readWholeFile("File03.c");
            std::string expectedFileContent = readWholeFile("FileRes03.c");

            Assert::IsTrue(!workFileContent.empty() && !expectedFileContent.empty());

            char *szFileContent = const_cast<char*>(workFileContent.c_str());
            removeComments(szFileContent);

            Assert::AreEqual(expectedFileContent.c_str(), szFileContent);
        }

        TEST_METHOD(ProcessingFiles20)
        {
            std::string workFileContent = readWholeFile("File20.c");
            std::string expectedFileContent = readWholeFile("FileRes20.c");

            Assert::IsTrue(!workFileContent.empty() && !expectedFileContent.empty());

            char *szFileContent = const_cast<char*>(workFileContent.c_str());
            removeComments(szFileContent);

            Assert::AreEqual(expectedFileContent.c_str(), szFileContent);
        }

#if 0
        TEST_METHOD(ProcessingUglyFiles1)
        {
            std::string workFileContent = readWholeFile("Ugly01.cpp");
            std::string expectedFileContent = readWholeFile("UglyRes01.cpp");

            Assert::IsTrue(!workFileContent.empty() && !expectedFileContent.empty());

            char *szFileContent = const_cast<char*>(workFileContent.c_str());
            removeComments(szFileContent);

            Assert::AreEqual(expectedFileContent.c_str(), szFileContent);
        }
#endif

    };
}