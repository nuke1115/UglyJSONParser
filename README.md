# UglyJSONParser
![GitHub License](https://img.shields.io/github/license/nuke1115/UglyJSONParser)
![GitHub Release](https://img.shields.io/github/v/release/nuke1115/UglyJSONParser)
CMake 3.20

UglyJSONParser : C++���� Ÿ��-�����ϰ� JSON�� �Ľ��ϰ� ����ϰ� ���ִ� ���¼ҽ� ũ�ν� �÷��� ���̺귯��.

## ����:

1. [�Ұ�](#anchor-introduction)
    + [UglyJSONParser��?](#anchor-what-is-UglyJSONParser)
    + [UglyJSONParser�� Ư¡](#anchor-UglyJSONParser-features)
    + [UglyJSONParser�� �Ѱ�](#anchor-UglyJSONParser-limitations)
2. [��ġ](#anchor-UglyJSONParser-installation)
    + [�ý��� �䱸 ����](#anchor-UglyJSONParser-system-spec-required)
    + [CMake�� UglyJSONParser�� �����ϱ�](#anchor-UglyJSONParser-with-CMake)
    + [Visual Studio 2022���� UglyJSONParser�� ����ϱ�](#anchor-use-UglyJSONParser-in-vs-2022)
    + [���� �ڵ�](#anchor-UglyJSONParser-examples)
3. [API ����](#anchor-UglyJSONParser-API-docs)
4. [���� ���� ����](#anchor-UglyJSONParser-FAQ)
5. [�η�](#anchor-UglyJSONParser-other-info)
    + [�⿩ ���̵����(���� �߰� ����)](#anchor-UglyJSONParser-contribution-guide)
    + [������](#anchor-UglyJSONParser-creator-info)
    + [������ �ڷ��](#anchor-UglyJSONParser-references)

---
<span id="anchor-introduction"></span>
# 1. �Ұ�

<span id="anchor-what-is-UglyJSONParser"></span>
## UglyJSONParser��?
UglyJSONParser��
1. C++������ ���ߵ� ���¼ҽ� JSON�ļ� ���̺귯�� �Դϴ�.
2. Ÿ���� �����Ǿ��־�, �߸��� Ÿ������ �����ϴ°��� ���� �������ݴϴ�.
3. ����� �����մϴ�.
4. ���� �÷������� ��� �����մϴ�.
5. ���/������ �̿� ��� �����Դϴ�.

---

<span id="anchor-UglyJSONParser-features"></span>
## UglyJSONParser�� Ư¡

1. ������ Ÿ��.
    + ����� �� Ÿ���� �������ְ�, �� Ÿ�԰��� ��ȯ�� �Ұ����ϵ��� �����Ͽ�, �߸��� Ÿ������ �����ϴ°��� ���� �����մϴ�.
    + ��, NumberŸ���� int�� double�� ��ȯ�� �����մϴ�.
2. ũ�ν� �÷��� ����.
    + CMake�� ���̺귯���� �� ȯ�濡 �°� ���� �� �� �ֵ��� �Ͽ�, ���� ���� �÷������� ��� �����մϴ�.
3. ����� �����մϴ�.
    + �����ϰ� ��忡 ������ �ʿ� ����, []�� .AsŸ��() ���� �����ϰ� ���� �����Ϳ� ���� �����մϴ�.
    + ���� ������� �����ִ� Ŭ������ �����Ͽ�, ������ ���� �а� �� �� �ֽ��ϴ�.
    + ��带 �����ϴ°��� �����ִ� Ŭ������ �־�, ����ڴ� ������ �����Ϳ� �����ϴ°Ϳ��� �Ű澵 �� �ֽ��ϴ�.
<span id="anchor-UglyJSONParser-limitations"></span>
## UglyJSONParser�� �Ѱ�

1. �Ϻ� �̽������� ���� ó���� �����ϴ�.
    + ���� \\\\ , \\" �� �����ϸ�, �� �̿��� �̽������� ���ڴ� '���� �״�� ����˴ϴ�'
2. ������ ������ ������� �ʽ��ϴ�.
    + ��Ƽ ������ ȯ�濡��, �ϳ��� jsonƮ���� �����Ѵٸ�, ����ġ ���� ������ ���� �� �ֽ��ϴ�.
3. ������ Ÿ��.
    + json ������ �������� ������ �� �ֽ��ϴ�.

---
<span id="anchor-UglyJSONParser-installation"></span>
# 2. ��ġ
<span id="anchor-UglyJSONParser-system-spec-required"></span>
## �ý��� �䱸 ����

### ����

���� : v1.0

�䱸�ϴ� �ּ� c++ ���� : c++ 20

---

### �̸� ����� .lib��

---

�÷��� ���� ���� : Visual Studio 2022 (v143)

Windows SDK ���� : 10.0

��Ÿ�� ���̺귯�� : Release => MD , Debug => MDd

�ּ� �ٽ� ���� ��� : Gm- ����

���� : Release ������ => UglyJSONParser.lib , Debug ������ => UglyJSONParser-d.lib

---
### CMake

�䱸�ϴ� �ּ� CMake ���� : 3.20

---
<span id="anchor-UglyJSONParser-with-CMake"></span>
## CMake�� UglyJSONParser�� �����ϱ�

<details>
<summary>��ġ��/����</summary>

1. �ҽ��ڵ�� build����, CMakeLists.txt�� �ִ� UglyJSONParser_v1.0_CMake.zip ������ ���ϴ� ������ ���������մϴ�.

2. ��ɾ ���� ������ ���α׷�(ex. powershell, shell, cmd ...)�� ���������� ���� �Ǵ�, �׳� ������ ��, �ش� ��ġ�� �̵��մϴ�.

3. ���� ������ ������ build������ �̵��մϴ�.

4. �� ��ġ���� cmake .. ��ɾ �����մϴ�.
    + �̶�, �ڽ��� ����� ��ü��,���ʷ�����, (����ϴ� ��ü���̳� ���ʷ����Ϳ� ���� ����������)� ���� Ÿ������ ���� ������ �����մϴ�.

5. ��ɾ ���������� ����ƴٸ�, �ڽ��� ����ϴ� ��ü���̳� ���ʷ����Ϳ� �´� ���� ��ɾ �����մϴ�.
    + ���� �ܰ迡�� ���� Ÿ���� �����ϴ� ��ü���̳� ���ʷ������� ����, �� �ܰ迡�� ���� Ÿ���� �����մϴ�.
    + ������Ʈ(���̺귯��)�� �̸��� UglyJSONParser�Դϴ�.

6. ������� build/output ������ ����˴ϴ�.

7. ����� ����� �̸���, �ڽ��� ������ Ÿ�Կ� ���� ���� (-Ÿ��)�� ���·� Ÿ���� ������ִ°��� ����˴ϴ�. 

8. ������� ������ϵ���, �ڽ��� ���ϴ� ��η� �̵����ݴϴ�.

</details>

---
<span id="anchor-use-UglyJSONParser-in-vs-2022"></span>
## Visual Studio 2022���� UglyJSONParser�� ����ϱ�

<details>
<summary>��ġ��/����</summary>

1. UglyJSONParser�� lib���ϵ�� ��� ������ ���ִ� Include������ UglyJSONParser ������ �ٿ�ε�, �Ǵ� �����Ͽ� �ڽ��� ���ϴ� ��ҿ� �����صӴϴ�.

    �Ƹ� Releases �ǿ��� ���ϰ� �� ������ �ٿ�ε� ���� �� �����̴ϴ�.
    �̶�, Include������ lib���� ���ִ� ������ ��ġ�� �޶� �˴ϴ�.

    ![�̹���_2-1](./README_FILES/2-1.PNG)

2. �� ���̺귯���� ����� ������Ʈ�� ����, ������Ʈ �Ӽ��� ���ϴ�.

    ![�̹���_2-2](./README_FILES/2-2.PNG)

3. ���� �Ӽ� -> ��Ŀ -> �Ϲ����� �߰� ���̺귯�� ���͸� �׸� ���� �� lib�� �ִ� ������ ��ġ�� ���� �� �ٿ��ֱ� �մϴ�.

    ![�̹���_2-3](./README_FILES/2-3.PNG)

4. ���� �Ӽ� -> ��Ŀ -> �Է����� �߰� ���Ӽ� �׸� ���� �ַ���� ������ �˸��� lib������ �̸��� �����ݴϴ�.

    Release �����̸� UglyJSONParser.lib��, Debug�����̸� UglyJSONParser-d.lib�� �����ݴϴ�.

    ��, �� �κ��� ����ڰ� ���̺귯���� �̸��� �ٸ��� �����ߴٸ�, �� �̸��� �����ָ� �˴ϴ�.

    ![�̹���_2-4](./README_FILES/2-4.PNG)

5. ���� �Ӽ� -> VC++ ���͸��� �ܺ� include ���͸��� ��������� ���ִ� ������ �ּҸ� �����ݴϴ�.
    
   �� �׸񿡼� �����ִ� ������ �ּҴ� #include <> �� �˻� ���� �ּ��̴�.

   ���� C:\a\b�� ����� �ְ�, �� �׸� C:\a �� �����־��ٸ�, #include \<b\���_�̸�.hpp> �� ���·� ��� �����ϴ�.

    ![�̹���_2-5](./README_FILES/2-5.PNG)

</details>

---
<span id="anchor-UglyJSONParser-examples"></span>
## ���� �ڵ�

1. ���Ͽ��� �о���� �����ϱ�.

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
    //�ʿ��� ������ ����
    UglyJSONParser::JSONParser parser;
    UglyJSONParser::RootNode root;

    //json���Ͽ��� ������ �о�� root��忡 JSONTree ����
    parser.BuildJSONTreeFromFile(".\\testing\\json.json", root);

    //JSONTree���� ���� �о����
    std::cout << "Hello : " << root["Hello"].AsString() << '\n';
    std::cout << "Int : " << root["Int"].AsInt() << '\n';
    std::cout << "float AsDouble : " << root["float"].AsDouble() << '\n';
    std::cout << "float AsInt : " << root["float"].AsInt() << '\n';

    std::cout << "Array 0 : " << root["array"][0].AsInt() << '\n';
    std::cout << "Array 3 : " << root["array"][3].AsBool() << '\n';
    std::cout << "Array 4 : " << root["array"][4].AsBool() << '\n';

    std::cout << "Object Key : " << root["object"]["key"].AsString() << '\n';

    std::cout << "nose : " << root["nose"].AsInt() << '\n';


    //�� ����
    std::cout << "before : Hello : " << root["Hello"].AsString() << '\n';
    root["Hello"] = "and O'men";
    std::cout << "after : Hello : " << root["Hello"].AsString() << '\n';

    //���Ͽ� JSONTree�� �� ����
    parser.SaveJSONTreeToFile(".\\testing\\json.json", root);

    return 0;
}
```

2. string���� �о����
```cpp
#include <UglyJSONParser/UglyJSONParserIncludeHeader.hpp>
#include <iostream>

int main()
{
    //�ʿ��� ������ ����
    UglyJSONParser::JSONParser parser;
    UglyJSONParser::RootNode root;
    std::string json = "{\"key\":\"value and this is \\\"value\\\"\",   \"arr\" : [1,1e+4,1.234]}";

    //string�� ������� JSONTree ����
    parser.BuildJSONTreeFromString(json, root);


    //�� �о����
    std::cout << "key : " << root["key"].AsString() << '\n';
    std::cout << "arr 0 : " << root["arr"][0].AsInt() << '\n';
    std::cout << "arr 1 : " << root["arr"][1].AsInt() << '\n';
    std::cout << "arr 2 : " << root["arr"][2].AsDouble() << '\n';

    return 0;
}
```

---
<span id="anchor-UglyJSONParser-API-docs"></span>
# 3. API ����

[UglyJSONParser v1.0 API Documents](https://github.com/nuke1115/LibraryDocumentsStorage/blob/main/UglyJSONParserDocuments/API_AND_REFERENCES/v1.0/README_API_DOCUMENTS.md)

---
<span id="anchor-UglyJSONParser-FAQ"></span>
# 4. ���� ���� ����

**����** : �� ������ �����ڰ� �߰����� ���� �̽��� ���� �ذ���� �ۼ��Ǿ����� �ʽ��ϴ�. ���� ���ο� �̽��� �߰��Ѵٸ� �����ڿ��� �����ϰų�, �ش� �������丮�� new issue�� ���شٸ�, ������ �� ���� ���� ���� ������Ʈ �ɰ��Դϴ�.

Q: LNK 2038������ �߻��մϴ�.
A: ������ Ȯ���غ��ʽÿ�:
1. �ַ���� ���� : Debug �������� Release ������ .lib�� ����߽��ϱ�?
2. ��Ÿ�� ���̺귯���� ��ġ�մϱ�?

---
<span id="anchor-UglyJSONParser-other-info"></span>
# 5. �η�
<span id="anchor-UglyJSONParser-contribution-guide"></span>
## �⿩ ���̵����:
(���� �غ���� �ʾҽ��ϴ�.)

---

<span id="anchor-UglyJSONParser-creator-info"></span>
## ������:

������: nuke1115

����ó:

[X(�� Ʈ����)](https://x.com/lysrhythmgamer)

Discord : yellowsticker_ / �������#7701

[github](https://github.com/nuke1115)

---
<span id="anchor-UglyJSONParser-references"></span>
## ������ �ڷ��

[json ���� ����](json.org)

[wikipedia : tree](https://en.wikipedia.org/wiki/Tree_(abstract_data_type))

[jsoncpp](https://github.com/open-source-parsers/jsoncpp?tab=readme-ov-file)