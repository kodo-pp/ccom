#pragma once
#include <ccom/rasterizer.hpp>

#include <memory>
#include <list>

namespace ccom::composition {

// TODO: Add templates

class Object {
public:
    explicit Object(std::weak_ptr<Object> parent = nullptr);
    virtual ~Object() = default;

    virtual void draw(Rasterizer& raster, const std::vector<char> format) const = 0;

    geometry::RelativePoint get_position() const;
    geometry::Point get_absolute_position() const;
    void set_position(const geometry::Point& position);

protected:
    std::list<std::shared_ptr<Object>> children;
    std::weak_ptr<Object> parent;
    geometry::Point position;
};

class GeometryObject : public Object {
public:
    explicit GeometryObject(const geometry::Object& geom, Object* parent = nullptr);
    virtual ~GeometryObject() = default;

    virtual void draw(Rasterizer& raster, const std::vector<char> format) const override;

protected:
    geometry::Object geom;
}

} // namespace ccom::composition
