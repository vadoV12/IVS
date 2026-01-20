//======= Copyright (c) 2025, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - test suite
//
// $NoKeywords: $ivs_project_1 $white_box_tests.cpp
// $Author:     Andrej Vadovsky <xvadova00@stud.fit.vutbr.cz>
// $Date:       $2025-02-19
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Andrej Vadovsky
 * 
 * @brief Implementace testu hasovaci tabulky.
 */

#include <vector>

#include "gtest/gtest.h"

#include "white_box_code.h"

using namespace ::testing;

//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy hasovaci tabulky, testujte nasledujici:
// 1. Verejne rozhrani hasovaci tabulky
//     - Vsechny funkce z white_box_code.h
//     - Chovani techto metod testuje pro prazdnou i neprazdnou tabulku.
// 2. Chovani tabulky v hranicnich pripadech
//     - Otestujte chovani pri kolizich ruznych klicu se stejnym hashem 
//     - Otestujte chovani pri kolizich hashu namapovane na stejne misto v 
//       indexu
//============================================================================//

/*** Konec souboru white_box_tests.cpp ***/
class EmptyHashMap : public Test{
protected:
    hash_map_t* map;
};

class NonEmptyHashMap : public Test{
    void SetUp() override{
        map=hash_map_ctor();
        hash_map_put(map,"key1",5);
        hash_map_put(map,"key2",10);
        hash_map_put(map,"key3",15);
        hash_map_put(map,"key4",20);
        hash_map_put(map,"key5",25);  
        hash_map_put(map,"key6",30);
        hash_map_put(map,"key7",35);
        hash_map_put(map,"key8",40);
        hash_map_put(map,"key9",45);      
    }
protected:
    hash_map_t* map;
};

TEST_F(EmptyHashMap,hash_map_ctor) 
{
    map=hash_map_ctor();
    ASSERT_EQ(8,map->allocated);
    
}

TEST_F(EmptyHashMap,hash_map_put)
{
    map=hash_map_ctor();
    hash_map_put(map,"key1",5);
    hash_map_put(map,"key2",10);
    hash_map_put(map,"key3",15);
    hash_map_put(map,"key4",20);
    hash_map_put(map,"key5",25);
    size_t count=0;
    for(int i=0;i<5;i++)
    {
        if(map->first->value==5 || map->first->value==10 || map->first->value==15 || map->first->value==20 || map->first->value==25)
        {
            count++;
        }
        map->first->value=map->first->next->value;
    }
    ASSERT_EQ(count,5);
}

TEST_F(EmptyHashMap,hash_map_size)
{
    map=hash_map_ctor();
    size_t size=0;
    size=hash_map_size(map);
    ASSERT_EQ(size,map->used);
}

TEST_F(EmptyHashMap,hash_map_dtor)
{
    map=hash_map_ctor();
    hash_map_dtor(map);
    ASSERT_TRUE(map->allocated==0);
}

TEST_F(EmptyHashMap,hash_map_clear)
{
    map=hash_map_ctor();
    hash_map_clear(map);
    ASSERT_EQ(map->used,0);
}

TEST_F(EmptyHashMap,hash_map_capacity)
{
    map=hash_map_ctor();
    ASSERT_EQ(map->allocated,hash_map_capacity(map));
}


TEST_F(EmptyHashMap,hash_map_reserve)
{
    map=hash_map_ctor();
    auto mapless=map->used-1;
    int result=hash_map_reserve(map,mapless); 
    ASSERT_EQ(result,MEMORY_ERROR);
    int result3=hash_map_reserve(map,map->allocated); 
    ASSERT_EQ(result3,OK);
    auto maple=map->used+1;
    int result2=hash_map_reserve(map,maple); 
    ASSERT_EQ(result2,OK);
}


TEST_F(EmptyHashMap,hash_map_contains) 
{
    map=hash_map_ctor();
    ASSERT_FALSE((hash_map_contains(map,"key1")));
    ASSERT_FALSE((hash_map_contains(map,"ajo")));
}

TEST_F(EmptyHashMap,hash_map_remove)
{
    map=hash_map_ctor();
    EXPECT_EQ(hash_map_remove(map,"key1"),KEY_ERROR);
    EXPECT_EQ(hash_map_remove(map,"ajo"),KEY_ERROR);
}

TEST_F(EmptyHashMap,hash_map_get)
{
    map=hash_map_ctor();
    int cau=8;
    EXPECT_EQ(hash_map_get(map,"key1",&cau),KEY_ERROR);
    EXPECT_EQ(hash_map_get(map,"key1meheheh",&cau),KEY_ERROR);
}

TEST_F(EmptyHashMap,hash_map_pop)
{
    map=hash_map_ctor();
    int cau=8;
    ASSERT_EQ(hash_map_pop(map,"key2",&cau),KEY_ERROR);
    ASSERT_EQ(hash_map_pop(map,"key1",&cau+1),KEY_ERROR);
    ASSERT_EQ(hash_map_pop(map,"key3",&cau+2),KEY_ERROR);
    ASSERT_EQ(hash_map_pop(map,"key1meheheh",&cau),KEY_ERROR);
}

TEST_F(NonEmptyHashMap,hash_map_size)
{
    size_t size=0;
    size=hash_map_size(map);
    ASSERT_EQ(size,map->used);
}
TEST_F(NonEmptyHashMap,hash_map_reserve)
{
    auto mapless=map->used-1;
    int result=hash_map_reserve(map,mapless); 
    ASSERT_EQ(result,VALUE_ERROR);
    int result3=hash_map_reserve(map,map->allocated); 
    ASSERT_EQ(result3,OK);
    EXPECT_TRUE((hash_map_contains(map,map->first->key)));      //reserve maze itemy ked dochadza k realokacii
    auto maple=map->used+1;
    int result2=hash_map_reserve(map,maple); 
    ASSERT_EQ(result2,OK);
    int result4=hash_map_reserve(map,1000000000000000000);
    ASSERT_EQ(result4,MEMORY_ERROR);
}

TEST_F(NonEmptyHashMap,hash_map_clear)
{
    hash_map_clear(map);
    ASSERT_EQ(map->used,0);
}

TEST_F(NonEmptyHashMap,hash_map_capacity)
{
    ASSERT_EQ(map->allocated,hash_map_capacity(map));

}

TEST_F(NonEmptyHashMap,hash_map_dtor)
{
    hash_map_dtor(map);
    ASSERT_TRUE(map->allocated==0);
}

TEST_F(NonEmptyHashMap,hash_map_get) 
{
    int cau=45; 
    EXPECT_EQ(hash_map_get(map,map->first->key,&cau),OK);
    EXPECT_EQ(hash_map_get(map,"key1meheheh",&cau),KEY_ERROR);
}

TEST_F(NonEmptyHashMap,hash_map_pop)
{
    int cau=8;
    EXPECT_EQ(hash_map_pop(map,map->first->next->key,&cau),OK);
    EXPECT_EQ(hash_map_pop(map,map->first->key,&cau),OK);
    EXPECT_EQ(hash_map_pop(map,map->last->key,&cau),OK);
    EXPECT_EQ(hash_map_pop(map,"key1meheheh",&cau),KEY_ERROR);
}

TEST_F(NonEmptyHashMap,hash_map_remove)
{
    EXPECT_EQ(hash_map_remove(map,map->first->key),OK);
    EXPECT_EQ(hash_map_remove(map,"key1meheheh"),KEY_ERROR);
}

TEST_F(NonEmptyHashMap,hash_map_ctor) 
{
    map=hash_map_ctor();
    ASSERT_EQ(8,map->allocated);
}

TEST_F(NonEmptyHashMap,hash_map_put)
{
    auto node=hash_map_put(map,"cauko",5);
    int i=0;
    do
    {
        i++;
        node=hash_map_put(map,"cauko",i);
    }while(hash_map_put(map,"cauko",i)!=KEY_ALREADY_EXISTS);
    
}

TEST_F(NonEmptyHashMap,hash_map_contains) 
{
    EXPECT_TRUE(hash_map_contains(map,"key1"));
    ASSERT_FALSE(hash_map_contains(map,"key1meheheh"));
}

TEST_F(EmptyHashMap,hash_collision)
{
    map=hash_map_ctor();
    ASSERT_TRUE(hash_map_put(map,"abc",5)==OK);
    ASSERT_TRUE(hash_map_put(map,"cba",10)==OK);
    int value=0;
    EXPECT_EQ(hash_map_get(map,"abc",&value),OK);
    EXPECT_EQ(value,5);
    EXPECT_EQ(hash_map_get(map,"cba",&value),OK);
    EXPECT_EQ(value,10);
    EXPECT_EQ(hash_map_pop(map,"abc",&value),OK);
    EXPECT_EQ(value,5);
    EXPECT_EQ(hash_map_get(map,"cba",&value),OK);
    EXPECT_EQ(value,10);
}

TEST_F(EmptyHashMap,hashkey_collision2)
{
    map=hash_map_ctor();
    ASSERT_TRUE(hash_map_put(map,"key1",5)==OK);
    ASSERT_TRUE(hash_map_put(map,"key2",5)==OK);
    int value=0;
    EXPECT_EQ(hash_map_get(map,"key1",&value),OK);
    EXPECT_EQ(value,5);
    EXPECT_EQ(hash_map_get(map,"key2",&value),OK);
    EXPECT_EQ(value,5);
    EXPECT_EQ(hash_map_pop(map, "key1",&value),OK);
    EXPECT_EQ(value,5);
    EXPECT_EQ(hash_map_get(map,"key2",&value),OK);
    EXPECT_EQ(value,5);
}


