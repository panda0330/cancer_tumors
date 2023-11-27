#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main()
{
    vector<string> code_number, clump_thickness, uniformity_cell_size, uniformity_cell_shape, marginal_adhesion, single_epithelial_cell_size, bare_nuclei, bland_chromatin, normal_nucleoli, mitoses, tumor_class;
    int total_patients = 0, total_benign = 0, total_malignant = 0, total_invalid_patient = 0;
    fstream initial_file, result_file;
    vector<vector<string>> content;
    vector<vector<int>> content_int;
    vector<string> row;
    string line, word;

    code_number.clear();
    clump_thickness.clear();
    uniformity_cell_shape.clear();
    uniformity_cell_size.clear();
    marginal_adhesion.clear();
    single_epithelial_cell_size.clear();
    bare_nuclei.clear();
    bland_chromatin.clear();
    normal_nucleoli.clear();
    mitoses.clear();
    tumor_class.clear();

    initial_file.open("unformatted_data_v1.0.0.csv", ios::in);

    if (!initial_file)
    {
        cout << "File not opened!";
    }
    else
    {
        while (getline(initial_file, line))
        {
            row.clear();

            stringstream str(line);

            while (getline(str, word, ','))
                row.push_back(word);
            content.push_back(row);
        }
        initial_file.close();
    }
    total_patients = content.size();    

    for (int i = 0; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {
            switch (j)
            {
            case 0:
                code_number.push_back(content[i][j]);
                break;
            case 1:
                clump_thickness.push_back(content[i][j]);
                break;
            case 2:
                uniformity_cell_size.push_back(content[i][j]);
                break;
            case 3:
                uniformity_cell_shape.push_back(content[i][j]);
                break;
            case 4:
                marginal_adhesion.push_back(content[i][j]);
                break;
            case 5:
                single_epithelial_cell_size.push_back(content[i][j]);
                break;
            case 6:
                bare_nuclei.push_back(content[i][j]);
                break;
            case 7:
                bland_chromatin.push_back(content[i][j]);
                break;
            case 8:
                normal_nucleoli.push_back(content[i][j]);
                break;
            case 9:
                mitoses.push_back(content[i][j]);
                break;
            case 10:
                tumor_class.push_back(content[i][j]);
                break;
            default:
                break;
            }
        }        
        if (clump_thickness[i] == "?" || uniformity_cell_shape[i] == "?" || uniformity_cell_size[i] == "?" || marginal_adhesion[i] == "?" || single_epithelial_cell_size[i] == "?" || bare_nuclei[i] == "?" || bland_chromatin[i] == "?" || normal_nucleoli[i] == "?" || mitoses[i] == "?")
        {
            total_invalid_patient += 1;
        }
        else if (stoi(uniformity_cell_size[i]) <= 2)
        {
            if (stoi(bare_nuclei[i]) <= 3)
            {
                tumor_class[i] = "2";
                total_benign += 1;
            }
            else
            {
                if (stoi(bland_chromatin[i]) <= 2)
                {
                    if (stoi(marginal_adhesion[i]) <= 3)
                    {
                        tumor_class[i] = "4";
                        total_malignant += 1;
                    }
                    else 
                    {
                        tumor_class[i] = "2";
                        total_benign += 1;
                    }
                }
                else
                {
                    tumor_class[i] = "4";
                    total_malignant += 1;
                }
                    
            }
        }
        else
        {
            if (stoi(uniformity_cell_shape[i]) <= 2)
            {
                if (stoi(clump_thickness[i]) <= 5)
                {
                    tumor_class[i] = "2";
                    total_benign += 1;
                }
                else
                {
                    tumor_class[i] = "4";
                    total_malignant += 1;
                }                    
            }
            else
            {
                if (stoi(uniformity_cell_size[i]) <= 4)
                {
                    if (stoi(bare_nuclei[i]) <= 2)
                    {
                        if (stoi(marginal_adhesion[i]) <= 3)
                        {
                            tumor_class[i] = "2";
                            total_benign += 1;
                        }
                        else
                        {
                            tumor_class[i] = "4";
                            total_malignant += 1;
                        }                            
                    }
                    else
                    {
                        if (stoi(clump_thickness[i]) <= 6)
                        {
                            if (stoi(uniformity_cell_size[i]) <= 3)
                            {
                                tumor_class[i] = "4";
                                total_malignant += 1;
                            }
                            else
                            {
                                if (stoi(marginal_adhesion[i]) <= 5)
                                {
                                    tumor_class[i] = "2";
                                    total_benign += 1;
                                }
                                else
                                {
                                    tumor_class[i] = "4";
                                    total_malignant += 1;
                                }                                    
                            }
                        }
                        else
                        {
                            tumor_class[i] = "4";
                            total_malignant += 1;
                        }                            
                    }
                }
                else
                {
                    tumor_class[i] = "4";
                    total_malignant += 1;
                }                    
            }
        }
    }    

    result_file.open("results.csv", ios::out);

    if (!result_file)
    {
        cout << "File not created!\n";
    }
    else
    {
        for (int i = 0; i < content.size(); i++)
        {
            if (tumor_class[i] == "2")
            {
                result_file << clump_thickness[i] << "," << uniformity_cell_size[i] << "," << uniformity_cell_shape[i] << "," << marginal_adhesion[i] << ","
                    << single_epithelial_cell_size[i] << "," << bare_nuclei[i] << "," << bland_chromatin[i] << "," << normal_nucleoli[i] << "," << mitoses[i] << "," << "Benign";
            }
            else if (tumor_class[i] == "4")
            {
                result_file << clump_thickness[i] << "," << uniformity_cell_size[i] << "," << uniformity_cell_shape[i] << "," << marginal_adhesion[i] << ","
                    << single_epithelial_cell_size[i] << "," << bare_nuclei[i] << "," << bland_chromatin[i] << "," << normal_nucleoli[i] << "," << mitoses[i] << "," << "Malignant";
            }                
            else
            {
                result_file << clump_thickness[i] << "," << uniformity_cell_size[i] << "," << uniformity_cell_shape[i] << "," << marginal_adhesion[i] << ","
                    << single_epithelial_cell_size[i] << "," << bare_nuclei[i] << "," << bland_chromatin[i] << "," << normal_nucleoli[i] << "," << mitoses[i] << "," << "0";
            }                

            result_file << "\n";
        }        
        result_file.close();
    }
    cout << "Total Patients Processed = " << total_patients << "\n";
    cout << "Total Benign = " << total_benign << "\n";
    cout << "Total Malignant = " << total_malignant << "\n";
    cout << "Total Invalid Patient = " << total_invalid_patient << "\n";
    return 0;   
}
