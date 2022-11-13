#include <boost/program_options.hpp>
// 'reading_file' 异常类在errors.hpp中声明
#include <boost/program_options/errors.hpp>
#include <iostream>

namespace opt = boost::program_options;

int main(int argc, char** argv) {
    opt::options_description desc("All options");
    /**
     * @brief 命令行选项 apples oranges name help
     *  命令行简称 a o
     * ->default_value() 设置默认值
     */
    desc.add_options()("apples,a", opt::value<int>()->default_value(10), "how many apples do you have?")(
        "oranges,o", opt::value<int>(), "how many oranges do you have?")("name", opt::value<std::string>(),
                                                                         "your name")("help", "produce help message");
    opt::variables_map vm;
    opt::store(opt::parse_command_line(argc, argv, desc), vm);
    opt::notify(vm);
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    /**
     * @brief 从“apples_oranges.cfg” 配置文件添加丢失的选项
     *  你也可以提供一个可用坐输入流（istreamable）的对象作为‘parse_config_file’的第一个
     *  参数'char' 模板参数将被传递给底层的std::basic_istream对象
     */

    try {
        opt::store(opt::parse_config_file<char>("../config/apples_oranges.cfg", desc), vm);
    } catch (const opt::reading_file& e) {
        std::cout << "Failed to open file 'apples_oranges.cfg' : " << e.what();
    }

    opt::notify(vm);
    if (vm.count("name")) {
        std::cout << "Hi, " << vm["name"].as<std::string>() << "!\n";
    }

    std::cout << "Fruits count: " << vm["apples"].as<int>() + vm["oranges"].as<int>() << std::endl;

    return 0;
}