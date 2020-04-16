#include "FamilyTree.hpp"
#include "doctest.h"
using namespace family;
using namespace std;
Tree T("me");


TEST_CASE("main test"){
    T.addMother("me","m").addFather("me","f");
    T.addMother("m","mm").addFather("m","mf");
    T.addMother("f","fm").addFather("f","ff");
    T.addMother("mm","mmm").addFather("mm","mmf");
    T.addMother("fm","fmm").addFather("fm","fmf");
    T.addMother("ff","ffm").addFather("ff","fff");
    T.addMother("mf","mfm").addFather("mf","mff");
    T.addFather("mmm","mmmf").addMother("mmm","mmmm");
    T.addFather("mmf","mmff").addMother("mmf","mmfm");
    T.addFather("mff","mfff").addMother("mff","mffm");
    T.addFather("fff","ffff").addMother("fff","fffm");
    T.addFather("ffm","ffmf").addMother("ffm","ffmm");
    T.addFather("fmm","fmmf").addMother("fmm","fmmm");
    T.addFather("mfm","mfmf").addMother("mfm","mfmm");
    T.addFather("fmf","fmff").addMother("fmf","fmfm");
    string ans;
    SUBCASE("find fathers"){
        CHECK(T.find("father")=="f");
        ans=T.find("grandfather");
        CHECK((ans=="ff"||ans=="mf"));
        ans=T.find("great-grandfather");
        CHECK((ans=="fff"||ans=="mff"||ans=="mmf"||ans=="fmf"));
        ans=T.find("great-great-grandfather");
        CHECK((ans=="mfff"||ans=="mmff"||ans=="mmmf"||ans=="mfmf"||
        ans=="ffff"||ans=="fmff"||ans=="fmmf"||ans=="ffmf"));
    }
    SUBCASE("find mothers"){
        CHECK(T.find("mother")=="m");
        ans=T.find("grandmother");
        CHECK((ans=="fm"||ans=="mm"));
        ans=T.find("great-grandmother");
        CHECK((ans=="ffm"||ans=="mfm"||ans=="mmm"||ans=="fmm"));
        ans=T.find("great-great-grandmother");
        CHECK((ans=="mffm"||ans=="mmfm"||ans=="mmmm"||ans=="mfmm"||
        ans=="fffm"||ans=="fmfm"||ans=="fmmm"||ans=="ffmm"));
    }
    SUBCASE("relation one generation up"){
        CHECK(T.relation("f")=="father");
        CHECK(T.relation("m")=="mother");
    }
    SUBCASE("relation two generation up"){
        CHECK(T.relation("mf")=="grandfather");
        CHECK(T.relation("mm")=="grandmother");
        
        CHECK(T.relation("ff")=="grandfather");
        CHECK(T.relation("fm")=="grandmother");
    }
    SUBCASE("relation three generation up"){
        CHECK(T.relation("fmf")=="great-grandfather");
        CHECK(T.relation("fmm")=="great-grandmother");
        CHECK(T.relation("fff")=="great-grandfather");
        CHECK(T.relation("ffm")=="great-grandmother");
        
        CHECK(T.relation("mmf")=="great-grandfather");
        CHECK(T.relation("mmm")=="great-grandmother");
        CHECK(T.relation("mff")=="great-grandfather");
        CHECK(T.relation("mfm")=="great-grandmother");
    }
    SUBCASE("relation four generation up"){
        CHECK(T.relation("mfmf")=="great-great-grandfather");
        CHECK(T.relation("mfmm")=="great-great-grandmother");
        CHECK(T.relation("mfff")=="great-great-grandfather");
        CHECK(T.relation("mffm")=="great-great-grandmother");
        CHECK(T.relation("mmmf")=="great-great-grandfather");
        CHECK(T.relation("mmmm")=="great-great-grandmother");
        CHECK(T.relation("mmff")=="great-great-grandfather");
        CHECK(T.relation("mmfm")=="great-great-grandmother");
        
        CHECK(T.relation("ffmf")=="great-great-grandfather");
        CHECK(T.relation("ffmm")=="great-great-grandmother");
        CHECK(T.relation("ffff")=="great-great-grandfather");
        CHECK(T.relation("fffm")=="great-great-grandmother");
        CHECK(T.relation("fmmf")=="great-great-grandfather");
        CHECK(T.relation("fmmm")=="great-great-grandmother");
        CHECK(T.relation("fmff")=="great-great-grandfather");
        CHECK(T.relation("fmfm")=="great-great-grandmother");
    }
    SUBCASE("relation unrelated"){
        CHECK(T.relation("a")=="unrelated");
        CHECK(T.relation("")=="unrelated");
        CHECK(T.relation("  ")=="unrelated");
        CHECK(T.relation("       h          k-sn            ")=="unrelated");
    }
   
    SUBCASE("remove one leaf"){
        T.remove("ffff");
        T.remove("ffmf");
        T.remove("fmff");
        T.remove("mfff");
        T.remove("mmff");
        T.remove("mmmf");
        T.remove("mfmf");
        
        CHECK(T.relation("ffff")=="unrelated");
        CHECK(T.relation("ffmf")=="unrelated");
        CHECK(T.relation("fmff")=="unrelated");
        CHECK(T.relation("mfff")=="unrelated");
        CHECK(T.relation("mmff")=="unrelated");
        CHECK(T.relation("mmmf")=="unrelated");
        CHECK(T.relation("mfmf")=="unrelated");

        CHECK(T.find("great-great-grandfather")=="fmmf");
    }
    SUBCASE("remove branch"){
       
        T.remove("fmm");
        T.remove("ffm");
        T.remove("mmm");
        T.remove("mfm");

        CHECK(T.relation("ffm")=="unrelated");
        CHECK(T.relation("fmm")=="unrelated");
        CHECK(T.relation("mmm")=="unrelated");
        CHECK(T.relation("mfm")=="unrelated");
        
        CHECK(T.relation("ffmm")=="unrelated");
        CHECK(T.relation("ffmf")=="unrelated");
        CHECK(T.relation("mmmm")=="unrelated");
        CHECK(T.relation("mfmm")=="unrelated");
        CHECK(T.relation("fmmm")=="unrelated");

        CHECK(T.relation("fffm")=="great-great-grandmother");
        CHECK(T.relation("mmfm")=="great-great-grandmother");
        CHECK(T.relation("mffm")=="great-great-grandmother");
        CHECK(T.relation("fmfm")=="great-great-grandmother");

        T.remove("f");
        CHECK(T.relation("m")=="mother");
        CHECK(T.relation("mm")=="grandmother");
        CHECK(T.relation("mf")=="grandfather");
        CHECK(T.relation("mmf")=="great-grandfather");
        CHECK(T.relation("mff")=="great-grandfather");

        ans=T.find("great-grandfather");
        CHECK((ans=="mmf"||ans=="mff"));
       
        ans=T.find("great-great-grandmother");
        CHECK((ans=="mmfm"||ans=="mffm"));
        
        
        CHECK(T.find("grandmother")=="mm");
        CHECK(T.find("grandfather")=="mf");
        CHECK(T.find("mother")=="m");
    }
     SUBCASE("ERR: undocumented relation"){
        CHECK_THROWS_WITH(T.find("great-great-grandfather"),"undocumented relation");
        CHECK_THROWS_WITH(T.find("great-grandmother"),"undocumented relation");
        CHECK_THROWS_WITH(T.find("father"),"undocumented relation");
        //never existed
        CHECK_THROWS_WITH(T.find("great-great-great-grandfather"),"undocumented relation");
        CHECK_THROWS_WITH(T.find("great-great-great-grandmother"),"undocumented relation");
        CHECK_THROWS_WITH(T.find("grdklwg sda"),"undocumented relation");
        CHECK_THROWS_WITH(T.find("great"),"undocumented relation");
        CHECK_THROWS_WITH(T.find("great-"),"undocumented relation");
        CHECK_THROWS_WITH(T.find("m"),"undocumented relation");
    }
    SUBCASE("ERR: can't remove undocumented member"){
   
        CHECK_THROWS_WITH(remove("great-great-great-grandmother"),"can't remove undocumented member");
        CHECK_THROWS_WITH(remove("ffff"),"can't remove undocumented member");
        CHECK_THROWS_WITH(remove("mmm"),"can't remove undocumented member");
        CHECK_THROWS_WITH(remove("mother"),"can't remove undocumented member");
        CHECK_THROWS_WITH(remove("f"),"can't remove undocumented member");

        CHECK_THROWS_WITH(remove("m "),"can't remove undocumented member");
        CHECK_THROWS_WITH(remove(" m"),"can't remove undocumented member");
        CHECK_THROWS_WITH(remove(""),"can't remove undocumented member");
        CHECK_THROWS_WITH(remove("      "),"can't remove undocumented member");
    }

    SUBCASE("add overlap- name change"){
        T.addMother("me","mother");
        CHECK(T.relation("m")=="unrelated");
        CHECK(T.find("grandfather")=="mf");
        T.addFather("mother","grandpa");
        CHECK(T.relation("mf")=="unrelated");
        CHECK(T.relation("grandpa")=="grandfather");
    }
    SUBCASE("line"){
        T.addMother("me","m").addMother("m","mm")
        .addMother("mm","mmm").addMother("mmm","mmmm")
        .addMother("mmmm","mmmmm").addMother("mmmmm","mmmmmm")
        .addMother("mmmmmm","mmmmmmm").addMother("mmmmmmm","mmmmmmmm")
        .addMother("mmmmmmmm","mmmmmmmmm").addMother("mmmmmmmmm","mmmmmmmmmm");
        CHECK(T.relation("m")=="mother");
        CHECK(T.relation("mmmmmmmmmm")=="great-great-great-great-great-great-great-great-grandmother");
        CHECK(T.find("great-great-great-great-great-great-great-great-grandmother")=="mmmmmmmmmm");
        T.remove("m");
        CHECK(T.relation("mmmmmmmmm")=="unrelated");
        CHECK(T.relation("m")=="unrelated");
        CHECK_THROWS_WITH(T.find("mother"),"undocumented relation");

    }

    

}
