cmake_minimum_required(VERSION 3.15)

project(playground CXX C)

# ———— Dependencies ————
# Vulkan
find_package(Vulkan REQUIRED FATAL_ERROR)
