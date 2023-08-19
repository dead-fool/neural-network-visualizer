#include <neuralNetworkParser.h>

NpyArray::npz_t getAllNumpyArray(const char* file = "activity.npz")
{
    // read NPY array file
    NpyArray::npz_t arr1;
    NpyArray arr;
    const LPCSTR ret = arr.LoadNPZ(file, arr1);

    if (ret != NULL) {
        std::cout << ret << " '" << file << "'\n";
        throw "Error opening file";
    }

    NpyArray::npz_t::iterator it = arr1.begin();



    // print array metadata
    std::cout << "Size " << arr1.size() << "\n";
    //std::cout << "Size in bytes " << arr.SizeBytes() << "\n";
    while (it != arr1.end()) {
        std::cout << "Key: " << it->first << std::endl;

        std::cout << "Dimensions:";
        for (size_t s : it->second.Shape())
            std::cout << " " << s;
        std::cout << "\n";

        std::cout << "Number of values: " << it->second.NumValue() << "\n";
        
        std::cout << "Data" << std::endl;
        int z = 0;
        for (auto d : it->second.DataVector<float_t>()) {
            std::cout << d << " "; z++;
            if (z == 15) break;
        }
        std::cout << std::endl;
        //std::cout << it->second.DataVector<uint8_t>() << std::endl;
        //std::cout << it->second.Data() << std::endl;
        
        std::cout << "Size in bytes: " << it->second.SizeBytes() << "\n";

        if (typeid(int) == it->second.ValueType())
            std::cout << "Value type: int\n";
        if (typeid(float) == it->second.ValueType())
            std::cout << "Value type: float\n";

        std::cout << "Values order: " << (it->second.ColMajor() ? "col-major\n" : "row-major\n");
        ++it;
        std::cout << std::endl;
    }
    return arr1;
}




NpyArray getSelectedNumpyArray(const char* layer, const char* file = "activity.npz")
{
    // read NPY array file
    NpyArray arr;
    const LPCSTR ret = arr.LoadNPZ(file, layer);

    if (ret != NULL) {
        std::cout << ret << " '" << file << "'\n";
        throw "Error opening file";
    }
    return arr;
}


int notm(int argc, const char** argv)
{
    if (argc != 2) {
        std::cout << "Usage: TinyNPY <array_file>\n";
        return -1;
    }

    // read NPY array file
    //NpyArray arr;
    //NpyArray::npz_t arr1;
    //const LPCSTR ret = arr.LoadNPZ(argv[1], arr1);

    // read NPZ arrays file: specific array
    NpyArray arr;
    const LPCSTR ret = arr.LoadNPZ("activity.npz", "fc4");

    // read NPZ arrays file: all arrays
    //NpyArray::npz_t arrays;
    //const LPCSTR ret = arr.LoadNPZ(argv[1], arrays);
    //NpyArray& arr = arrays.begin()->second;

    if (ret != NULL) {
        std::cout << ret << " '" << argv[1] << "'\n";
        return -2;
    }

    // print array metadata
    std::cout << "Dimensions:";
    for (size_t s : arr.Shape())
        std::cout << " " << s;
    std::cout << "\n";
    std::cout << "Number of values: " << arr.NumValue() << "\n";
    std::cout << "Size in bytes: " << arr.SizeBytes() << "\n";
    if (typeid(int) == arr.ValueType())
        std::cout << "Value type: int\n";
    if (typeid(float) == arr.ValueType())
        std::cout << "Value type: float\n";
    std::cout << "Values order: " << (arr.ColMajor() ? "col-major\n" : "row-major\n");
    return EXIT_SUCCESS;
}
