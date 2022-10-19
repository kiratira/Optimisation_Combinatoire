#include "pch.h"
#include "CppUnitTest.h"
#include "../Grasp/main.h"
#include "../Grasp/main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GraspTest
{
	TEST_CLASS(initTest)
	{
	public:

		TEST_METHOD(initEntree)
		{
			Entree entree;

			Assert::AreEqual((unsigned char)0, entree.nbCouverture);
			Assert::AreEqual((unsigned char)0, entree.nbEmplacement);
			Assert::AreEqual(0.0f, entree.coutImpression);
			Assert::AreEqual(0.0f, entree.coutFabrication);
		}

		TEST_METHOD(initSortie)
		{
			Solution sortie;

			Assert::AreEqual(0, (int)sortie.nbPlaques);
			Assert::AreEqual(true, sortie.actif);
			Assert::AreEqual(FLT_MAX, sortie.coutTotal);
		}

		TEST_METHOD(initFunction)
		{
			Solution sortie;
			unsigned char nbEmplacement = 2;
			sortie.nbPlaques = 2;

			init(&sortie, &nbEmplacement);

			Assert::AreEqual(0U, sortie.nbImpression[1]);
			Assert::AreEqual((unsigned char)0, sortie.agencement[3]);
		}

	};

	TEST_CLASS(lectureTest)
	{
	public:

		TEST_METHOD(isFile1Accessible)
		{
			Entree file1, expected;
			expected.nbCouverture = 3;
			expected.nbEmplacement = 4;
			expected.coutImpression = 13.44;
			expected.coutFabrication = 18676;

			std::ifstream myReadFile("../file1.in");
			
			Assert::AreEqual(myReadFile.is_open(), true);

		}

		TEST_METHOD(lectureFile1)
		{
			Entree file1, expected;
			expected.nbCouverture = 3;
			expected.nbEmplacement = 4;
			expected.coutImpression = 13.44;
			expected.coutFabrication = 18676;

			lecture(&file1, "file1.in");

			Assert::AreEqual(expected.nbCouverture, file1.nbCouverture);
			Assert::AreEqual(expected.nbEmplacement, file1.nbEmplacement);
			Assert::AreEqual(expected.coutImpression, file1.coutImpression);
			Assert::AreEqual(expected.coutFabrication, file1.coutFabrication);
		}

		TEST_METHOD(lectureEchec)
		{
			Entree file2, expected;
			expected.nbCouverture = 3;
			expected.nbEmplacement = 4;
			expected.coutImpression = 13.44;
			expected.coutFabrication = 18676;

			lecture(&file2, "file2.in");

			//Assert::ExpectException<int>(lecture);
		}


	};

	TEST_CLASS(checkPlaques) {

	public:

		TEST_METHOD(plaqueValide) {
			std::vector<unsigned char> agencement = { 0, 1, 2, 3 };
			unsigned char nbCouv = 4;

			bool result = checkValiditePlaque(&agencement, &nbCouv);

			Assert::AreEqual(result, true);
		}

		TEST_METHOD(plaqueNonValide) {
			std::vector<unsigned char> agencement = { 0, 1, 2, 2 };
			unsigned char nbCouv = 4;

			bool result = checkValiditePlaque(&agencement, &nbCouv);

			Assert::AreEqual(result, false);
		}
	};

	TEST_CLASS(calculDuCout) {

		TEST_METHOD(calculBonInt) {
			std::vector<unsigned char> agencement = { 0, 1, 2, 3 };
			std::vector<unsigned int> nbImpression = { 10000 };
			unsigned short int nbPlaques = 1;
			unsigned char nbEmplacement = 4;
			float coutTotal = 0, coutImp = 1, coutFab = 100;

			calculCout(&agencement,
				&nbImpression,
				&nbPlaques,
				&nbEmplacement,
				&coutTotal,
				&coutImp,
				&coutFab);

			Assert::AreEqual(coutTotal, (float)10100);
		}

		TEST_METHOD(calculBonFloat) {
			std::vector<unsigned char> agencement = { 0, 1, 2, 3 };
			std::vector<unsigned int> nbImpression = { 10000 };
			unsigned short int nbPlaques = 1;
			unsigned char nbEmplacement = 4;
			float coutTotal = 0, coutImp = 1.2 , coutFab = 100.3;

			calculCout(&agencement,
				&nbImpression,
				&nbPlaques,
				&nbEmplacement,
				&coutTotal,
				&coutImp,
				&coutFab);

			Assert::AreEqual(coutTotal, 12100.3f);
		}
	};

}