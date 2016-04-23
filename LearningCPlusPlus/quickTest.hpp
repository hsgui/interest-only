#pragma once

#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include <map>
#include <assert.h>

namespace LearningCPP
{
    namespace QuickTest
    {
        template<typename... Ts>
        void iprintf(const char* format, Ts&&... params)
        {
            printf(format, std::forward<Ts>(params)...);
            printf("\n");
        }

        std::string getString()
        {
            char temp[123];
            sprintf_s(temp, sizeof(temp), "%s.pdi", "hellowWorldhellowWorld");

            // sprintf_s(temp, sizeof(temp), "%s.pdi", "hellowWorld");
            // the following std::move will still use another address to store the data.

            return temp;
        }

        void testMove(std::string& t)
        {
            std::string s = getString();
            iprintf("%p", &s[0]);
            // If the s.size() < _BUF_SIZE (16), it will call "memmove" eventually
            // otherwise, move assignment will just assign the pointer address.
            t = std::move(s);
            iprintf("s=%s, t=%s", s.c_str(), t.c_str());
            iprintf("%p", &t[0]);

            std::string m = t;
            iprintf("t=%s, m=%s", t.c_str(), m.c_str());
        }

        void testCeil()
        {
            size_t a = 1;
            size_t b = 110;

            uint8_t c = (uint8_t)(ceil(((double)a * 100) / b));
            std::cout << c << std::endl;
        }

        struct Pair
        {
            int a;
            int b;
        };

        void getSSS(std::vector<Pair>& p_sss)
        {
            p_sss.reserve(10);
            Pair p;
            p.a = 1;
            p.b = 2;
            p_sss.emplace_back(std::move(p));
        }

        void printAndRemove(const std::shared_ptr<int>& p)
        {
            std::cout << "value=" << (*p) << std::endl;
        }

        class TestVirtual
        {
        public:
            virtual void print() = 0;
        };

        class TestVirtualB : public TestVirtual
        {
        public:
            void print() { std::cout << "TestVirtualB" << std::endl; }
        };

        class TestVirtualC : public TestVirtualB
        {
        public:
            void print() { std::cout << "TestVirtualC" << std::endl; }
        };

        void testVirtual()
        {
            TestVirtual* t1 = new TestVirtualC();
            t1->print();

            delete t1;
        }

        struct SegmentBlob
        {
            int a;
            int b;
        };

        typedef uint32_t SegmentTag;
        SegmentTag abcd1 = 10;
        const SegmentTag* abcd1p = &abcd1;

        struct PredefinedSegmentTag
        {
            inline static SegmentTag GetDocDataSegmentTag()
            {
                return *(reinterpret_cast<const SegmentTag*>("docd"));
            }

            const SegmentTag c_docDataSegmentTag = *((const SegmentTag*)("docd"));
            const SegmentTag c_metaWordSegmentTag = *(reinterpret_cast<const SegmentTag*>("mtwd"));
            const SegmentTag c_streamSizeSegmentTag = *(reinterpret_cast<const SegmentTag*>("stsz"));
            const SegmentTag c_metaStreamSegmentTag = *(reinterpret_cast<const SegmentTag*>("mtsm"));
            const SegmentTag c_annotationSegmentTag = *(reinterpret_cast<const SegmentTag*>("annt"));
            const SegmentTag c_updateSubstringSegmentTag = *(reinterpret_cast<const SegmentTag*>("upss"));
        };

        static const PredefinedSegmentTag c_PredefinedSegmentTag;

        static const SegmentTag c_updateSubstringSegmentTag = *(reinterpret_cast<const SegmentTag*>("upss"));

        void test()
        {
            std::vector<int> a{ 1,2,3,7,4,5 };
            std::vector<int> b{ 6,3,2,7,9,1 };
            std::set<int> combined;
            combined.insert(a.begin(), a.end());
            combined.insert(b.begin(), b.end());

            iprintf("%s, %d", "hello world", 5);

            std::string t;
            testMove(t);
            iprintf("%s", t.c_str());

            testCeil();

            uint64_t i1 = 11;
            printf("result: %12I64X\n", i1);

            
            std::vector<std::shared_ptr<int>> sss;
            sss.emplace_back(new int(40));

            auto p = std::move(sss[0]);
            assert(sss[0] == nullptr);
            assert(p != nullptr);
            printAndRemove(std::move(p));
 
            uint64_t x = 0;
            uint64_t y = 18446744072645148502;
            std::cout << "x-y:" << x - y << std::endl;

            testVirtual();

            std::map<int, SegmentBlob> blobs;
            blobs[1] = SegmentBlob{ 1, 2 };

            std::vector<SegmentBlob> tttttt;
            tttttt.emplace_back(SegmentBlob{ 1,3 });

            static const uint32_t t_num = *((const uint32_t*)("abcd"));
            printf("hello. %d\n", t_num);

            printf("%d\n", sizeof(PredefinedSegmentTag) / sizeof(SegmentTag));

            return;
        }
    }
}