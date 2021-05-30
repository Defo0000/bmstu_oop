#pragma once

class base_builder
{
public:
    base_builder() = default;
    ~base_builder() = default;
};

class model_builder : public base_builder
{
public:
    ~model_builder() = default;
private:
};
