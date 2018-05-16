#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <iostream>
#include <libxml++/libxml++.h>

#include <stdlib.h>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ofstream out2("amountDistrict.txt");
    ofstream out3("amountAddress.txt");

    locale::global(locale(""));

    xmlpp::TextReader reader("data.xml");
    Glib::ustring lastDistrict = "";

    vector<Glib::ustring> district;
    vector<int> districtAmount;

    Glib::ustring lastAddress = "";

    vector<Glib::ustring> address;
    vector<int> addressAmount;

    try
    {
        while(reader.read())
        {
            int depth = reader.get_depth();

            if (depth == 2)
            {
                if (reader.get_name() == "district")
                {
                    reader.read();

                    Glib::ustring str = reader.get_value();

                    if (str.find(' ') != string::npos)
                    {
                        str = str.substr(0, str.find(' '));
                    }

                    if (str != lastDistrict)
                    {
                        district.push_back(str);
                        districtAmount.push_back(0);
                        lastDistrict = str;
                    }

                    reader.read();
                }
                else if (reader.get_name() == "address")
                    {
                        reader.read();
                        Glib::ustring str = reader.get_value();

                        str = str.substr(0, str.find(" д") - 2);

                        if (str != lastAddress)
                        {
                            address.push_back(str);
                            addressAmount.push_back(0);
                            lastAddress = str;
                        }

                        reader.read();
                    }
                    else if (reader.get_name() == "amount")
                        {
                            reader.read();

                            int amount = atoi(reader.get_value().c_str());

                            districtAmount.back() += amount;
                            addressAmount.back() += amount;

                            reader.read();
                        }

            }
        }
    }

    catch(const exception& e)
    {
        cout << "Exception caught: " << e.what() << endl;

        return EXIT_FAILURE;
    }

    for(int i = 0; i < district.size(); i++)
    {
        out2 << district[i] << ": " << districtAmount[i] << endl;
    }

    for (int i = 0; i < address.size(); i++)
    {
        out3 << address[i] << ": " << addressAmount[i] << endl;
    }

    out2.close();
    out3.close();

    return EXIT_SUCCESS;
}
