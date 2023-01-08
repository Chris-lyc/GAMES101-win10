//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum){
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject)
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    // TO DO Implement Path Tracing Algorithm here
    
    Vector3f l_dir,l_indir;
    Intersection inter=intersect(ray);
    if(!inter.happened)//光线无相交
    {
        return {};
    }
    if(inter.obj->hasEmit())//本物体发光
    {
        return inter.emit;
    }
    // std::cout<<inter.normal<<std::endl;
    //inter为反射点 x为光源上一点
    Intersection x;
    float pdf_light;
    sampleLight(x,pdf_light);
    Ray ray_intertolight=Ray(inter.coords,(x.coords-inter.coords).normalized());
    
    Intersection tmp=intersect(ray_intertolight);

    if(abs(tmp.distance-(x.coords-inter.coords).norm())<EPSILON)//未被遮挡
    {
        l_dir=x.emit*inter.m->eval(ray.direction,ray_intertolight.direction,inter.normal)
                *dotProduct(ray_intertolight.direction,inter.normal)*dotProduct(-ray_intertolight.direction,x.normal)
                /pow((x.coords-inter.coords).norm(),2.0f)/pdf_light;
    }

    float ksi=get_random_float();
    
    if(ksi<=RussianRoulette)//俄罗斯轮盘赌 需要继续发射光线
    {
        Vector3f wi=inter.m->sample(ray.direction,inter.normal);
        Ray ray_intertoobj=Ray(inter.coords,wi);

        tmp=intersect(ray_intertoobj);
        if(tmp.happened==true)
        {
            l_indir=castRay(ray_intertoobj,depth)*inter.m->eval(ray.direction,ray_intertoobj.direction,inter.normal)
                    *dotProduct(ray_intertoobj.direction,inter.normal)
                    /inter.m->pdf(ray.direction,ray_intertoobj.direction,inter.normal)/RussianRoulette;
        }
    }

    return l_dir+l_indir;
}