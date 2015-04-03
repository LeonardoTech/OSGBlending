
#include "OSGEmpty.h"
#ifdef _DEBUG
#pragma comment(lib, "osgViewerd.lib")
#pragma comment(lib, "osgDBd.lib")
#pragma comment(lib, "OpenThreadsd.lib")
#pragma comment(lib, "osgd.lib")
#pragma comment(lib, "osgGAd.lib")
#else
#pragma comment(lib, "osgViewer.lib")
#pragma comment(lib, "osgDB.lib")
#pragma comment(lib, "OpenThreads.lib")
#pragma comment(lib, "osg.lib")
#pragma comment(lib, "osgGA.lib")
#endif
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgGA/GUIEventAdapter>
#include <osgViewer/ViewerEventHandlers>
#include <osg/StateSet>
#include <osg/Geode>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/Image>
#include <osg/Texture2D>
#include <osg/LineWidth>
#include <osg/Node>
#include <osg/Geometry>
#include <iostream>

using namespace osg;

osg::ref_ptr<osg::Node> createQuad()
{
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;

	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
	geom->setVertexArray(v.get());
	v->push_back(osg::Vec3(-1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, -1.f));
	v->push_back(osg::Vec3(1.f, 0.f, 1.f));
	v->push_back(osg::Vec3(-1.f, 0.f, 1.f));

	osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
	geom->setColorArray(c.get());
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
	c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
	c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
	c->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));

	osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
	geom->setNormalArray(n.get());
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
	n->push_back(osg::Vec3(0.f, -1.f, 0.f));

	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom.get());
	return geode.get();
}

osg::ref_ptr<osg::Geode> CreateBox()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	ref_ptr<ShapeDrawable> shape = new ShapeDrawable(new Box(Vec3(0,0,0),1.0, 10.0, 10.0), hints.get());
	ref_ptr<Material> material = new Material;
	ref_ptr<Texture2D> texture2d = new Texture2D;
	ref_ptr<Image> image;

	// set color
	shape->setColor(Vec4(0.5, 0.5, 0.5, 0.1));

	// set ratio
	hints->setDetailRatio(0.5);

	// set material
	material->setAmbient(Material::FRONT_AND_BACK, Vec4f(1.0, 1.0, 1.0, 1.0));
	material->setDiffuse(Material::FRONT_AND_BACK, Vec4f(1.0, 1.0, 1.0, 0.5));
	material->setSpecular(Material::FRONT_AND_BACK, Vec4f(1.0, 0.0, 0.0, 1.0));
	material->setShininess(Material::FRONT_AND_BACK, 6.0);

	//// set texture
	//image = osgDB::readImageFile("E:\\WorkSpace\\VCplusplus\\OSG\\OSGBlending\\x64\\Release\\diffuse.jpg");
	//if(image->valid())
	//{
	//	texture2d->setImage(image.get());
	//}

	// set state
	geode->getOrCreateStateSet()->setAttributeAndModes(material.get(), StateAttribute::ON);
	geode->getOrCreateStateSet()->setMode(GL_BLEND, StateAttribute::ON);
	geode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, StateAttribute::ON);
	//geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture2d.get(), StateAttribute::ON);
	geode->addDrawable(shape.get());
	return geode;
}
void main()
{
	ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	ref_ptr<Group> root = new Group();
	root->addChild(createQuad().get());
	root->addChild(CreateBox().get());
	viewer->setSceneData(root.get());
	viewer->realize();
	viewer->run();
}