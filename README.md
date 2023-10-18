# ZyfJSON - Cpp Json Parser 解析器


-   Yifan Zheng
-   2023/10
-   该 cpp json 项目主要参考 Milo Yip《从零开始的 JSON 库教程》https://github.com/miloyip/json-tutorial.git <br />以及 https://github.com/Yuan-Hang/Json.git, 通过该项目熟悉c++和stl相关特性。
-   小白一枚，编程新手，请大佬指教。

### 特点：333&444

1.  C++ 11 及以上, MSVC编译生成
2.  实现JSON解析器
3.  使用现代C++、STL
4.  googletest实现单元测试
5.  采用C++动态多态(polymorphism)特性实现Json数据类型<br /> [ Json, JsonStr, JsonNum, JsonLiteral, JsonArray, JsonObject ]

### 测试：
1.  MSVS创建一个空项目ZyfJSON，添加JSON.h、JsonData.h、ZyfJSON.cpp;<br />
    MSVS创建一个gtest测试项目，添加test.cpp、pch.h、pch.cpp。
2.  test.cpp中创建Json对象
    ```cpp  
    JsonObject obj;
    ```
3.  创建Parser解析器对象并初始化,参数1为待解析Json字符串，参数2为创建的Json对象

    ```cpp
    Parser p(" { "
            "\"n\" : null , "
            "\"f\" : false , "
            "\"t\" : true , "
            "\"i\" : 123 , "
            "\"s\" : \"abc\" , "
            "\"a\" : [ 1 , 2 , 3 ] , "
            "\"o\" : { \"1\" : [ \"str\" , 2 , 3 ], \"2\" : 222, \"3\" : 333 }"
            " } ", &obj);
    ```
4.  Parser解析器运行解析

    ```cpp
    p.parse();
    ```
5.  读取创建的Json对象中的数据

    ```cpp
    std::cout << obj["n"].getstr() <<std::endl ;
    std::cout << obj["o"]["1"][2].getnum() <<std::endl ;
    std::cout << obj["a"][2].getnum() <<std::endl ;
    ```
    或通过gtest进行测试

    ```cpp
    EXPECT_EQ(obj["o"]["2"].getnum(), 222);
	EXPECT_EQ(obj["o"]["3"].getnum(), 333);
    ```

6. release方式编译