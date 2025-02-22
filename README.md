# UglyJSONParser
![GitHub License](https://img.shields.io/github/license/nuke1115/UglyJSONParser)
![GitHub Release](https://img.shields.io/github/v/release/nuke1115/UglyJSONParser)
CMake 3.20

UglyJSONParser : C++에서 타입-안전하게 JSON을 파싱하고 사용하게 해주는 오픈소스 크로스 플랫폼 라이브러리.

## 목차:

1. [소개](#anchor-introduction)
    + [UglyJSONParser란?](#anchor-what-is-UglyJSONParser)
    + [UglyJSONParser의 특징](#anchor-UglyJSONParser-features)
    + [UglyJSONParser의 한계](#anchor-UglyJSONParser-limitations)
2. [설치](#anchor-UglyJSONParser-installation)
    + [시스템 요구 사항](#anchor-UglyJSONParser-system-spec-required)
    + [CMake로 UglyJSONParser를 빌드하기](#anchor-UglyJSONParser-with-CMake)
    + [Visual Studio 2022에서 UglyJSONParser를 사용하기](#anchor-use-UglyJSONParser-in-vs-2022)
    + [예제 코드](#anchor-UglyJSONParser-examples)
3. [API 문서](#anchor-UglyJSONParser-API-docs)
4. [자주 묻는 질문](#anchor-UglyJSONParser-FAQ)
5. [부록](#anchor-UglyJSONParser-other-info)
    + [기여 가이드라인(추후 추가 예정)](#anchor-UglyJSONParser-contribution-guide)
    + [제작자](#anchor-UglyJSONParser-creator-info)
    + [참고한 자료들](#anchor-UglyJSONParser-references)

---
<span id="anchor-introduction"></span>
# 1. 소개

<span id="anchor-what-is-UglyJSONParser"></span>
## UglyJSONParser란?
UglyJSONParser는
1. C++용으로 개발된 오픈소스 JSON파서 라이브러리 입니다.
2. 타입이 고정되어있어, 잘못된 타입으로 접근하는것을 거의 방지해줍니다.
3. 사용이 간편합니다.
4. 여러 플랫폼에서 사용 가능합니다.
5. 상업/비상업적 이용 모두 무료입니다.

---

<span id="anchor-UglyJSONParser-features"></span>
## UglyJSONParser의 특징

1. 고정된 타입.
    + 노드의 각 타입이 고정돼있고, 각 타입간의 변환이 불가능하도록 설계하여, 잘못된 타입으로 접근하는것을 거의 방지합니다.
    + 단, Number타입의 int와 double은 변환이 가능합니다.
2. 크로스 플랫폼 지원.
    + CMake로 라이브러리를 각 환경에 맞게 빌드 할 수 있도록 하여, 보다 많은 플랫폼에서 사용 가능합니다.
3. 사용이 간편합니다.
    + 복잡하게 노드에 접근할 필요 없이, []와 .As타입() 으로 간단하게 노드와 데이터에 접근 가능합니다.
    + 파일 입출력을 도와주는 클래스를 내장하여, 파일을 쉽게 읽고 쓸 수 있습니다.
    + 노드를 구축하는것을 도와주는 클래스가 있어, 사용자는 오로지 데이터에 접근하는것에만 신경쓸 수 있습니다.
<span id="anchor-UglyJSONParser-limitations"></span>
## UglyJSONParser의 한계

1. 일부 이스케이프 문자 처리가 미흡하다.
    + 현재 \\\\ , \\" 만 지원하며, 그 이외의 이스케이프 문자는 '들어온 그대로 저장됩니다'
2. 스레드 안전이 보장되지 않습니다.
    + 멀티 스레드 환경에서, 하나의 json트리를 공유한다면, 예상치 못한 동작이 있을 수 있습니다.
3. 고정된 타입.
    + json 고유의 유동성을 저해할 수 있습니다.

---
<span id="anchor-UglyJSONParser-installation"></span>
# 2. 설치
<span id="anchor-UglyJSONParser-system-spec-required"></span>
## 시스템 요구 사항

### 공통

버전 : v1.0

요구하는 최소 c++ 버전 : c++ 20

---

### 미리 빌드된 .lib들

---

플랫폼 도구 집합 : Visual Studio 2022 (v143)

Windows SDK 버전 : 10.0

런타임 라이브러리 : Release => MD , Debug => MDd

최소 다시 빌드 기능 : Gm- 고정

종류 : Release 구성용 => UglyJSONParser.lib , Debug 구성용 => UglyJSONParser-d.lib

---
### CMake

요구하는 최소 CMake 버전 : 3.20

---
<span id="anchor-UglyJSONParser-with-CMake"></span>
## CMake로 UglyJSONParser를 빌드하기

<details>
<summary>펼치기/접기</summary>

1. 소스코드와 build폴더, CMakeLists.txt가 있는 UglyJSONParser_v1.0_CMake.zip 파일을 원하는 폴더에 압축해제합니다.

2. 명령어를 실행 가능한 프로그램(ex. powershell, shell, cmd ...)을 압축해제한 폴더 또는, 그냥 실행한 후, 해당 위치로 이동합니다.

3. 압축 해제한 폴더의 build폴더로 이동합니다.

4. 그 위치에서 cmake .. 명령어를 실행합니다.
    + 이때, 자신이 사용할 툴체인,제너레이터, (사용하는 툴체인이나 제너레이터에 따라서 선택적으로)어떤 빌드 타입인지 등의 설정을 설정합니다.

5. 명령어가 성공적으로 실행됐다면, 자신이 사용하는 툴체인이나 제너레이터에 맞는 빌드 명령어를 실행합니다.
    + 빌드 단계에서 빌드 타입을 설정하는 툴체인이나 제너레이터의 경우는, 이 단계에서 빌드 타입을 설정합니다.
    + 프로젝트(라이브러리)의 이름은 UglyJSONParser입니다.

6. 결과물은 build/output 폴더에 저장됩니다.

7. 저장된 결과물 이름을, 자신이 빌드한 타입에 따라 끝에 (-타입)의 형태로 타입을 명시해주는것이 권장됩니다. 

8. 결과물과 헤더파일들은, 자신이 원하는 경로로 이동해줍니다.

</details>

---
<span id="anchor-use-UglyJSONParser-in-vs-2022"></span>
## Visual Studio 2022에서 UglyJSONParser를 사용하기

<details>
<summary>펼치기/접기</summary>

1. UglyJSONParser의 lib파일들과 헤더 파일이 모여있는 Include폴더의 UglyJSONParser 폴더를 다운로드, 또는 빌드하여 자신이 원하는 장소에 저장해둡니다.

    아마 Releases 탭에서 편하게 두 파일을 다운로드 받을 수 있을겁니다.
    이때, Include폴더와 lib들이 모여있는 폴더의 위치는 달라도 됩니다.

    ![이미지_2-1](./README_FILES/2-1.PNG)

2. 이 라이브러리를 사용할 프로젝트를 열고, 프로젝트 속성을 엽니다.

    ![이미지_2-2](./README_FILES/2-2.PNG)

3. 구성 속성 -> 링커 -> 일반탭의 추가 라이브러리 디렉터리 항목에 조금 전 lib이 있는 폴더의 위치를 복사 및 붙여넣기 합니다.

    ![이미지_2-3](./README_FILES/2-3.PNG)

4. 구성 속성 -> 링커 -> 입력탭의 추가 종속성 항목에 현제 솔루션의 구성에 알맞은 lib파일의 이름을 적어줍니다.

    Release 구성이면 UglyJSONParser.lib을, Debug구성이면 UglyJSONParser-d.lib을 적어줍니다.

    단, 이 부분은 사용자가 라이브러리의 이름을 다르게 설정했다면, 그 이름을 적어주면 됩니다.

    ![이미지_2-4](./README_FILES/2-4.PNG)

5. 구성 속성 -> VC++ 디렉터리의 외부 include 디렉터리에 헤더파일이 모여있는 폴더의 주소를 적어줍니다.
    
   이 항목에서 적어주는 폴더의 주소는 #include <> 의 검색 시작 주소이다.

   만약 C:\a\b에 헤더가 있고, 저 항목에 C:\a 를 적어주었다면, #include \<b\헤더_이름.hpp> 의 형태로 사용 가능하다.

    ![이미지_2-5](./README_FILES/2-5.PNG)

</details>

---
<span id="anchor-UglyJSONParser-examples"></span>
## 예제 코드

1. 파일에서 읽어오고 저장하기.

json.json

```json
{
    "Hello": "World!",
    "Int": 1234,
    "float": 1.234000,
    "exponent": 1000,
    "array": [ 1, 2, 3, true, false ],
    "object": { "key": "value" },
    "null": null,
    "nose": -3000
}
```

```cpp
#include <UglyJSONParser/UglyJSONParserIncludeHeader.hpp>
#include <iostream>

int main()
{
    //필요한 변수들 선언
    UglyJSONParser::JSONParser parser;
    UglyJSONParser::RootNode root;

    //json파일에서 파일을 읽어와 root노드에 JSONTree 생성
    parser.BuildJSONTreeFromFile(".\\testing\\json.json", root);

    //JSONTree에서 값을 읽어오기
    std::cout << "Hello : " << root["Hello"].AsString() << '\n';
    std::cout << "Int : " << root["Int"].AsInt() << '\n';
    std::cout << "float AsDouble : " << root["float"].AsDouble() << '\n';
    std::cout << "float AsInt : " << root["float"].AsInt() << '\n';

    std::cout << "Array 0 : " << root["array"][0].AsInt() << '\n';
    std::cout << "Array 3 : " << root["array"][3].AsBool() << '\n';
    std::cout << "Array 4 : " << root["array"][4].AsBool() << '\n';

    std::cout << "Object Key : " << root["object"]["key"].AsString() << '\n';

    std::cout << "nose : " << root["nose"].AsInt() << '\n';


    //값 수정
    std::cout << "before : Hello : " << root["Hello"].AsString() << '\n';
    root["Hello"] = "and O'men";
    std::cout << "after : Hello : " << root["Hello"].AsString() << '\n';

    //파일에 JSONTree의 값 저장
    parser.SaveJSONTreeToFile(".\\testing\\json.json", root);

    return 0;
}
```

2. string에서 읽어오기
```cpp
#include <UglyJSONParser/UglyJSONParserIncludeHeader.hpp>
#include <iostream>

int main()
{
    //필요한 변수들 선언
    UglyJSONParser::JSONParser parser;
    UglyJSONParser::RootNode root;
    std::string json = "{\"key\":\"value and this is \\\"value\\\"\",   \"arr\" : [1,1e+4,1.234]}";

    //string을 기반으로 JSONTree 생성
    parser.BuildJSONTreeFromString(json, root);


    //값 읽어오기
    std::cout << "key : " << root["key"].AsString() << '\n';
    std::cout << "arr 0 : " << root["arr"][0].AsInt() << '\n';
    std::cout << "arr 1 : " << root["arr"][1].AsInt() << '\n';
    std::cout << "arr 2 : " << root["arr"][2].AsDouble() << '\n';

    return 0;
}
```

---
<span id="anchor-UglyJSONParser-API-docs"></span>
# 3. API 문서

[UglyJSONParser v1.0 API Documents](https://github.com/nuke1115/LibraryDocumentsStorage/blob/main/UglyJSONParserDocuments/API_AND_REFERENCES/v1.0/README_API_DOCUMENTS.md)

---
<span id="anchor-UglyJSONParser-FAQ"></span>
# 4. 자주 묻는 질문

**주의** : 이 문단은 제작자가 발견하지 못한 이슈에 대한 해결법은 작성되어있지 않습니다. 만약 새로운 이슈를 발견한다면 제작자에게 연락하거나, 해당 리포지토리에 new issue를 해준다면, 가능한 한 빠른 시일 내로 업데이트 될것입니다.

Q: LNK 2038오류가 발생합니다.
A: 다음을 확인해보십시오:
1. 솔루션의 구성 : Debug 구성에서 Release 구성용 .lib을 사용했습니까?
2. 런타임 라이브러리가 일치합니까?

---
<span id="anchor-UglyJSONParser-other-info"></span>
# 5. 부록
<span id="anchor-UglyJSONParser-contribution-guide"></span>
## 기여 가이드라인:
(아직 준비되지 않았습니다.)

---

<span id="anchor-UglyJSONParser-creator-info"></span>
## 제작자:

제작자: nuke1115

연락처:

[X(구 트위터)](https://x.com/lysrhythmgamer)

Discord : yellowsticker_ / 노란딱지#7701

[github](https://github.com/nuke1115)

---
<span id="anchor-UglyJSONParser-references"></span>
## 참고한 자료들

[json 공식 문서](json.org)

[wikipedia : tree](https://en.wikipedia.org/wiki/Tree_(abstract_data_type))

[jsoncpp](https://github.com/open-source-parsers/jsoncpp?tab=readme-ov-file)