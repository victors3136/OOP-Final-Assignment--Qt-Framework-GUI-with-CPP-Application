//
// Created by victor on 17/05/2023.
//

#ifndef A89_VICTORS3136_1_MASTERTEST_H
#define A89_VICTORS3136_1_MASTERTEST_H


#include <cassert>
#include "../Headers/Tutorial.h"
#include "../Headers/Repository/MemoryRepository.h"
#include "../Headers/Manager.h"

class MasterTest {
private:
    static void testTutorial() {
        /// test getters
        Tutorial t1{"C++ Compare char array with string", "Chris Kleisli", 350, 75, "https://stackoverflow"
                                                                                    ".com/questions/1195675/convert-a-char-to-stdstring"};
        assert(t1.getTitle() == "C++ Compare char array with string");
        assert(t1.getPresenter() == "Chris Kleisli");
        assert(t1.getDuration() == 350);
        assert(t1.getDuration() != 250);
        assert(t1.getLikes() == 75);
        assert(t1.getLink() == "https://stackoverflow.com/questions/1195675/convert-a-char-to-stdstring");
        assert(t1.getLink() != "this is not the right title");

        /// test setters

        Tutorial t2{"C++ Compare char array with string", "Chris Kleisli", 350, 75, "https://stackoverflow"
                                                                                    ".com/questions/1195675/convert-a-char-to-stdstring"};
        t2.setTitle("Some new title");
        assert(t2.getTitle() == "Some new title");
        t2.setPresenter("Name LastName");
        assert(t2.getPresenter() == "Name LastName");
        t2.setDuration(343);
        assert(t2.getDuration() == 343);
        t2.setLikes(43);
        assert(t2.getLikes() == 43);
        t2.setLink("https://stackoverflow.com/questions/72985855/libgcov-profiling-error-overwriting-an-existing"
                   "-profile-data-with-a-different");
        assert(t2.getLink() == "https://stackoverflow"
                               ".com/questions/72985855/libgcov-profiling-error-overwriting-an-existing-profile-data"
                               "-with-a-different");

        Tutorial t0;
        t0.setTitle("H");
        t0.setPresenter("O");
        t0.setLink("G");
        t0.setLikes(0);
        t0.setDuration(0);
        assert(t0.getTitle() == "H");
        assert(t0.getPresenter() == "O");
        assert(t0.getLink() == "G");
        assert(t0.getLikes() == 0);
        assert(t0.getDuration() == 0);

        /// test equality operators

        Tutorial t3{"This video", "has  different parameters", 0,0, "but ultimately leads to the same link"};
        Tutorial t4{"That other video", "seems different from the first",124, 999, "but ultimately leads to the same link"};
        assert(t3 == t4);
        Tutorial t5{"This video", "has different parameters", 1, 1, "and does not lead to the same place"};
        assert(t3 != t5);
        assert(t4 != t5);

        /// test << overloading
        Tutorial t6{"T", "D", 90, 10, "B"};
        std::ostringstream oss;
        oss << t6;

        std::string expectedOutput { "T|D|90|10|B" };
        assert(oss.str() == expectedOutput);
    };
    static void testRepo(){
        /// test add
        Tutorial t1, t2, t3, t4, t5;
        t1.setLink("Some");
        t2.setLink("Text");
        t3.setLink("That");
        t4.setLink("Differs");
        t5.setLink("Differs");
	    MemoryRepository repo1;
        assert(repo1.size() == 0);
		repo1.add(t1);
		try{
			repo1.add(t1);
			assert(false);
		}catch(const RepositoryError&err){
			assert(true);
			assert(std::string(err.what()) == std::string("Error: Tutorial already in repo\n"));
		}
        assert(repo1.size() == 1);
		repo1.add(t2);
	    try{
		    repo1.add(t2);
		    assert(false);
	    }catch(const RepositoryError&err){
		    assert(true);
		    assert(std::string(err.what()) == std::string("Error: Tutorial already in repo\n"));
	    }
        assert(repo1.size() == 2);
		repo1.add(t3);

	    try{
		    repo1.add(t3);
		    assert(false);
	    }catch(const RepositoryError&err){
		    assert(true);
		    assert(std::string(err.what()) == std::string("Error: Tutorial already in repo\n"));
	    }
        assert(repo1.size() == 3);
        repo1.add(t4);
        assert(repo1.size() == 4);
	    try{
		    repo1.add(t5);
		    assert(false);
	    }catch(const RepositoryError&err){
		    assert(true);
		    assert(std::string(err.what()) == std::string("Error: Tutorial already in repo\n"));
	    }
        assert(repo1.size() == 4);
        for(int i = 1; i < 100; i ++)
        {
            Tutorial t{std::to_string(i), std::to_string(i), i,i, std::to_string(i)};
            repo1.add(t);
        }
        assert(repo1.size() == 103);

        /// test remove
	    MemoryRepository repo2;
        t5.setLink("Differs more"); /// we want t4 != t5
	    try{
		    repo2.remove(t1);
		    assert(false);
	    }catch(const RepositoryError&err){
		    assert(true);
		    assert(std::string(err.what()) == std::string("Error: Tutorial does not exist\n"));
	    }
        repo2.add(t1);
        repo2.add(t2);
        repo2.add(t3);
        repo2.add(t4);
        repo2.add(t5);
        repo2.remove(t1);
        repo2.remove(t2);
        repo2.remove(t3);
        repo2.remove(t4);
        repo2.remove(t5);
	    try{
		    repo2.remove(t1);
		    assert(false);
	    }catch(const RepositoryError&err){
		    assert(true);
		    assert(std::string(err.what()) == std::string("Error: Tutorial does not exist\n"));
	    }
        for(int i = 0; i < 100; i ++)
        {
            Tutorial t{std::to_string(i), std::to_string(i), i,i, std::to_string(i)};
            repo2.add(t);
        }
        for(int i = 0; i < 100; i ++)
            repo2.remove(repo2[0]);

        /// test operator
	    MemoryRepository repo3;
        repo3.add(t1);
        repo3.add(t2);
        repo3.add(t3);
        repo3.add(t4);
        repo3.add(t5);
        for(int i = 0 ; i < repo3.size() - 1; i ++)
            for(int j = i + 1; j < repo3.size(); j ++)
                assert(repo3[i] != repo3[j]);
        assert(repo3[0] == t1);
        assert(repo3[1] == t2);
        assert(repo3[2] == t3);
        assert(repo3[3] == t4);
        assert(repo3[4] == t5);
        repo3.remove(repo3[1]);
        assert(repo3[1] == t3);
        assert(repo3[repo3.size() - 1] == t5);


        /// test modify elem
	    MemoryRepository repo4;
        repo4.add(t1);
        repo4.add(t2);
        repo4.add(t3);
        repo4.add(t4);
        repo4.add(t5);
		try{
			repo4.modifyMember(-1, 1, "woaj");
			assert(false);
		}catch(const RepositoryError& err){
			assert(true);
			assert(std::string(err.what()) == std::string("Error: Index does not represent a valid position inside "
														  "the repository\n"));
		}
        assert(repo4[0].getTitle() != "woaj");
	    try{
		    repo4.modifyMember(6, 1, "woaj");
		    assert(false);
	    }catch(const RepositoryError& err){
		    assert(true);
		    assert(std::string(err.what()) == std::string("Error: Index does not represent a valid position inside "
		                                                  "the repository\n"));
	    }
	    try{
		    repo4.modifyMember(0, -1, "woaj");
		    assert(false);
	    }catch(const RepositoryError& err){
		    assert(true);
		    assert(std::string(err.what()) == std::string("Error: No field by that name \n"));
	    }
        assert(repo4[0].getTitle() != "woaj");
        repo4.modifyMember(0, 1, "Woah");
        assert(repo4[0].getTitle() == "Woah");
        repo4.modifyMember(1, 2, "Woah");
        assert(repo4[1].getPresenter() == "Woah");
        repo4.modifyMember(2, 3, "12");
        assert(repo4[2].getDuration() == 12);
        repo4.modifyMember(3, 4, "0");
        assert(repo4[3].getLikes() == 0);
        repo4.modifyMember(4, 5, "https://www.youtube.com");
        assert(repo4[4].getLink() == "https://www.youtube.com");
    };
    static void testManager()
    {
	    std::string test_file = "blanktestfile.txt";
		std::ofstream f1(test_file, std::ios::trunc);
		f1.close();
	    /// test add
	    {
		    Manager man1;

		    man1.setRepoType(test_file, "html", test_file);
		    for (int i = 1; i < 100; i++)
			    man1.addTutorial(std::to_string(i), std::to_string(i), i, i, std::to_string(i));
		    man1.addTutorial("This is a title", "And this a name", 800, 1234, "but this' a link");
		    try
		    {
			    man1.addTutorial("This title is different", "So is the presenter", 900, 1342, "but this' a link");
			    assert(false);
		    } catch (const RepositoryError &err)
		    {
			    assert(true);
			    assert(std::string(err.what()) == std::string("Error: Tutorial already in repo\n"));
		    }
	    }
	    std::ofstream f2(test_file, std::ios::trunc);
	    f2.close();
		{
		    Manager man2;
			man2.setRepoType(test_file, "html", test_file);
		    for (int i = 1; i < 100; i++)
		    {
			    Tutorial t{std::to_string(i), std::to_string(i), i, i, std::to_string(i)};
			    man2.addTutorial(t);
			}
        }
	    std::ofstream f3(test_file, std::ios::trunc);
	    f3.close();
        /// test remove
	    {
		    Manager man3;
		    man3.setRepoType(test_file, "html", test_file);
		    for (int i = 0; i < 1024; i++)
			    man3.addTutorial(std::to_string(i), std::to_string(i), i, i, std::to_string(i));
		    for (int i = 0; i < 1024; i++)
			    try
			    {
				    man3.addTutorial(std::to_string(i), std::to_string(i), i, i, std::to_string(i));
				    assert(false);
			    } catch (const RepositoryError &err)
			    {
				    assert(true);
				    assert(std::string(err.what()) == std::string("Error: Tutorial already in repo\n"));
			    }
		    for (int i = 0; i < 1024; i++)
			    man3.removeTutorial(std::to_string(i));
		    for (int i = 0; i < 1024; i++)
			    try
			    {
				    man3.removeTutorial(std::to_string(i));
				    assert(false);
			    } catch (const RepositoryError &err)
			    {
				    assert(true);
				    assert(std::string(err.what()) == std::string("Error: Tutorial does not exist\n"));
			    }
	    }

	    std::ofstream f4(test_file, std::ios::trunc);
	    f4.close();
        /// test modify
	    {
		    Manager man4;
		    man4.setRepoType(test_file, "html", test_file);
		    for (int i = 0; i < 1024; i++)
			    man4.addTutorial(std::to_string(i), std::to_string(i), i, i, std::to_string(i));
		    for (int i = 0; i < 1023; i++)
			    try
			    {
				    man4.modifyField(i, "link", std::to_string(i + 1));
				    assert(false);
			    } catch (const RepositoryError &err)
			    {
				    assert(true);
				    assert(std::string(err.what()) ==
				           std::string("Error: This change would result in overlapping links\n"));
			    }
		    man4.modifyField(1023, "link", std::to_string(1024));
		    for (int i = 0; i < 32; i++)
			    man4.modifyField(i, "title", "dunno");
		    for (int i = 32; i < 64; i++)
			    man4.modifyField(i, "presenter", "not me");
		    for (int i = 96; i < 128; i++)
			    man4.modifyField(i, "duration", "10");
		    for (int i = 160; i < 192; i++)
			    man4.modifyField(i, "likes", "10");
		    for (int i = 192; i < 224; i++)
			    man4.modifyField(i, "link", std::to_string(-1 * i));
		    for (int i = 224; i < 256; i++)
			    try
			    {
				    man4.modifyField(i, "gabagoo", "ey toney");
				    assert(false);
			    } catch (const RepositoryError &err)
			    {
				    assert(true);
				    assert(std::string(err.what()) == std::string("Error: No field by that name\n"));
			    }
	    }

	    std::ofstream f5(test_file, std::ios::trunc);
	    f5.close();
        /// check get by presenter
	    {
		    Manager man5;
		    man5.setRepoType(test_file, "html", test_file);
		    for (int i = 1; i <= 1024; i++)
		    {
			    std::string istring = std::to_string(i);
			    Tutorial t{istring, istring, i, i, istring};
			    man5.addTutorial(t);
		    }
		    auto vectorOfAll = man5.getByPresenter("");
		    for (int i = 1; i <= 1024; i++)
		    {
			    std::string istring = std::to_string(i);
			    Tutorial t{istring, istring, i, i, istring};

			    auto retVal = man5.getByPresenter(std::to_string(i));
			    assert(std::find(retVal.begin(), retVal.end(), t) != retVal.end());
			    assert(std::find(vectorOfAll.begin(), vectorOfAll.end(), t) != vectorOfAll.end());
		    }
	    }
	    std::ofstream f(test_file, std::ios::trunc);
	    f.close();
    };

public:
    static void run(){
           MasterTest::testTutorial();
           MasterTest::testRepo();
           MasterTest::testManager();
    }
};


#endif //A89_VICTORS3136_1_MASTERTEST_H
