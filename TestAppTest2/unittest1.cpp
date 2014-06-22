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
    std::ifstream ifs(strFileName.c_str(), std::ios::in);

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
        TEST_METHOD(ComparingBase1)
        {
            char workContent[] = "// this is the comment";
            char expectedContent[] = "";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComparingBase2)
        {
            char workContent[] = "/* another comment */";
            char expectedContent[] = "";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComparingBase3)
        {
            char workContent[] = "text // comment";
            char expectedContent[] = "text ";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComparingBase4)
        {
            char workContent[]     = "text1 /* comment */ text2";
            char expectedContent[] = "text1  text2";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComparingComplex1)
        {
            char workContent[] = " text1 /**/ text2 /* */ text3 /* comment */ text4";
            char expectedContent[] = " text1  text2  text3  text4";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComparingComplex2)
        {
            char workContent[] = "/***  text    ***/";
            char expectedContent[] = "";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComparingComplex3)
        {
            char workContent[] = "/**  text  **/";
            char expectedContent[] = "";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComparingComplex4)
        {
            char workContent[] = "/**  text  **/ text";
            char expectedContent[] = " text";

            removeComments(workContent);

            Assert::AreEqual(expectedContent, workContent);
        }

        TEST_METHOD(ComparingComplex5)
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

        TEST_METHOD(ComparingMultiline1)
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

        TEST_METHOD(ComparingMultiline2)
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

        TEST_METHOD(ComparingMultiline3)
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

        TEST_METHOD(ComparingMultiline4)
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


        // ===============================================================================        
        TEST_METHOD(ComparingFiles1)
        {
            std::string workFileContent = readWholeFile("File1.c");
            std::string expectedFileContent = readWholeFile("FileRes1.c");

            char *szFileContent = const_cast<char*>(workFileContent.c_str());
            removeComments(szFileContent);

            Assert::AreEqual(expectedFileContent.c_str(), szFileContent);
        }

    };
}