# UglyJSONParser

## ����:

0. ���̺귯�� ����
1. ����
    + UglyJSONParser�� �����ΰ���?
    + Ư¡
    + �Ѱ�
2. ���̺귯�� ������
    + lib�� hpp�� ������Ʈ�� �߰��ϴ¹�(windows visual studio 2022)
3. API ����
    + ����
    + �ֿ� Ŭ���� �� �Լ����� ����Ʈ�� ��ɵ�
4. ���۷��� ����
    + �� Ŭ������ �Լ��� ����
5. ���� �ڵ�
6. �̽� �ذ��
7. �⿩ ���̵����(�غ���� ����)
8. ������
9. �ֱ� ����
10. ���̼���
11. ���鶧 �����ߴ� �ڷ��

---

# 0. ���̺귯�� ����:

���� : v1.0

�䱸�ϴ� �ּ� c++ ���� : c++ 20

�÷��� ���� ���� : Visual Studio 2022 (v143)

Windows SDK ���� : 10.0

��Ÿ�� ���̺귯�� : Release => MD , Debug => MDd
�ּ� �ٽ� ���� ��� : Gm- ����

���� : Release ������ => UglyJSONParser.lib , Debug ������ => UglyJSONParser-d.lib

������ ���� : ������� ����.

---
# 1. ����

## UglyJSONParser�� �����ΰ���?:

### UglyJSONParser��:
1. C++������ ���ߵ� ���� ���¼ҽ� JSON�ļ� ���̺귯�� �Դϴ�.
2. Ÿ���� �����Ǿ��־�, �߸��� Ÿ������ �����ϴ°� ��κ� �������ݴϴ�.
3. ����� ����� �ʽ��ϴ�.
4. ����/��� �뵵 ��� �����Դϴ�.


## Ư¡:

1. ������ Ÿ��.
    + UglyJSONParser�� Array,Object,Null,Number(long long,double),Bool,String,Root �� ���еǸ�, �� Ÿ�԰��� ��ȯ�� �Ұ��մϴ�.(Number �������� ��ȯ�� ����)
    + �̷� Ư¡���� ���� �ణ�� Ÿ�Ծ������� ì����ϴ�.
    + ��带 ������ �� �ٽ� �����ϴ� ������� Ÿ���� �ٲܼ� ������, **�̷��� ����� ������� �ʽ��ϴ�.**
2. ����� ����� �ʴ�.
    + �����ϰ� ������ �ҷ�����, �װ� �����ϰ�, �װ� �ļ��� ������ �� �ʿ䰡 �����ϴ�.
      
      �ܼ��� RootNode�� ���� ������ �ּҸ� �ļ��� �Է��ϸ�, JSONTree�� RootNode�� �������ݴϴ�.
    + �����Ϳ� �����ϴ°͵� []�� �����ϰ�, �����ϴ� ������ ���Ŀ� �˸��� .AsXXX() �� �����ϴ°� ���Դϴ�.
3. ����Ǿ��ִ� ���� ����� �Ŵ���.
    + ���̺귯���� ���� ������� �����ִ� Ŭ������ �����Ͽ�, ����ڰ� ������ json�����͸� �ٷ�°Ϳ��� ���� �����ϵ��� �����ݴϴ�.


## �Ѱ�:
1. ������ Ÿ��.
    + ������ Ÿ���̶�� Ư¡�� ���׸� �ٿ��ֱ⵵ ������, ������ JSON�� �����ο� ������ �̿����� ���ϵ��� �����ϴ� ������ �ϱ⵵ �մϴ�.
2. v1.0 ���� �����ڵ带 �������� �ʴ´�.
    + ������Ʈ�� �� ��ȹ�� ������, v1.0�������� �����ڵ�� ���������� ��ȯ�� �ȵ˴ϴ�.
3. v1.0 ���ؽ����� ������ �������� �ʴ´�.
4. ũ�ν� �÷����� ������ �����ϴ�.
    + cmake���� ������ �������� �ʾ�, �ٸ� �÷����̳� �����Ϸ��� ����Ϸ���, ����ڰ� ���� ȯ�濡 �°� �����ؾ� �˴ϴ�.

---

# 2. ���̺귯�� ������:

## lib�� hpp�� ������Ʈ�� �߰��ϴ¹�(windows visual studio 2022)

1. UglyJSONParser�� lib���ϵ�� ��� ������ ���ִ� Include������ UglyJSONParser ������ �ٿ�ε� �Ͽ� �ڽ��� ���ϴ� ��ҿ� �����صӴϴ�.

    �Ƹ� Releases �ǿ��� ���ϰ� �� ������ �ٿ�ε� ���� �� �����̴ϴ�.
    �̶�, Include������ lib���� ���ִ� ������ ��ġ�� �޶� �˴ϴ�.

    ![�̹���_2-1](./README_FILES/2-1.PNG)

2. �� ���̺귯���� ����� ������Ʈ�� ����, ������Ʈ �Ӽ��� ���ϴ�.

    ![�̹���_2-2](./README_FILES/2-2.PNG)

3. ���� �Ӽ� -> ��Ŀ -> �Ϲ����� �߰� ���̺귯�� ���͸� �׸� ���� �� lib�� �ִ� ������ ��ġ�� ���� �� �ٿ��ֱ� �մϴ�.

    ![�̹���_2-3](./README_FILES/2-3.PNG)

4. ���� �Ӽ� -> ��Ŀ -> �Է����� �߰� ���Ӽ� �׸� ���� �ַ���� ������ �˸��� lib������ �̸��� �����ݴϴ�.
   
   Release �����̸� UglyJSONParser.lib��, Debug�����̸� UglyJSONParser-d.lib�� �����ݴϴ�.

    ![�̹���_2-4](./README_FILES/2-4.PNG)

5. ���� �Ӽ� -> VC++ ���͸��� �ܺ� include ���͸��� ��������� ���ִ� ������ �ּҸ� �����ݴϴ�.
    
   �� �׸񿡼� �����ִ� ������ �ּҴ� #include <> �� �˻� ���� �ּ��̴�.

   ���� C:\a\b�� ����� �ְ�, �� �׸� C:\a �� �����־��ٸ�, #include \<b\���_�̸�.hpp> �� ���·� ��� �����ϴ�.

    ![�̹���_2-5](./README_FILES/2-5.PNG)


---

# 3. API ����:

[UglyJSONParser v1.0 API Documents](https://github.com/nuke1115/LibraryDocumentsStorage/blob/main/UglyJSONParserDocuments/API_AND_REFERENCES/v1.0/README_API_DOCUMENTS.md)


---

# 5. ���� �ڵ�:
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
# 6. �̽� �ذ��

**����** : �� ������ �����ڰ� �߰����� ���� �̽��� ���� �ذ���� �ۼ��Ǿ����� �ʽ��ϴ�. ���� ���ο� �̽��� �߰��Ѵٸ� �����ڿ��� �����ϰų�, �ش� �������丮�� new issue�� ���شٸ�, ������ �� ���� ���� ���� ������Ʈ �ɰ��Դϴ�.

### LNK 2038:
������ Ȯ���غ��ʽÿ�:
1. �ַ���� ���� : Debug �������� Release ������ .lib�� ����߽��ϱ�?
2. ��Ÿ�� ���̺귯���� ��ġ�մϱ�?

---
# 7. �⿩ ���̵����:

(���� �غ���� �ʾҽ��ϴ�.)

---

# 8. ������:

������: nuke1115

����ó:

[X(�� Ʈ����)](https://x.com/lysrhythmgamer)

Discord : yellowsticker_ / �������#7701

[github](https://github.com/nuke1115)

---
# 9. �ֱ� ����:

v1.0

---
# 10. ���̼���

License : MIT License

���ο뵵 �̿�, ����뵵 �̿� ��� �����Դϴ�.

---
# 11. ���鶧 �����ߴ� �ڷ��:

[json ���� ����](json.org)

[wikipedia : tree](https://en.wikipedia.org/wiki/Tree_(abstract_data_type))

[jsoncpp](https://github.com/open-source-parsers/jsoncpp?tab=readme-ov-file)