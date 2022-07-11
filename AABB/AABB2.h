/*
  Copyright (c) 2009 Erin Catto http://www.box2d.org
  Copyright (c) 2016-2018 Lester Hedges <lester.hedges+aabbcc@gmail.com>

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.

  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.

  3. This notice may not be removed or altered from any source distribution.

  ��δ���ı���Lester Hedges��һ��AABB����Ŀ��
  https://github.com/lohedges/aabbcc

  �ı��ֻ֧��2ά������ʹ��Vec2��ZY_Size������vector<float>
*/
#ifndef _AABB_H
#define _AABB_H

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <unordered_map>
#include <vector>
#include "../ZY_Engine/Node.h"
/// Null node flag.
const unsigned int NULL_NODE = 0xffffffff;
class Node;

    /*! \brief The axis-aligned bounding box object.

        Axis-aligned bounding boxes (AABBs) store information for the minimum
        orthorhombic bounding-box for an object. Support is provided for
        dimensions >= 2. (In 2D the bounding box is either a rectangle,
        in 3D it is a rectangular prism.)

        Class member functions provide functionality for merging AABB objects
        and testing overlap with other AABBs.
     */
    class AABB
    {
    public:
        /// Constructor.
        AABB();

        //! Constructor.
        /*! \param dimension
                The dimensionality of the system.
         */
        //AABB(unsigned int);

        //! Constructor.
        /*! \param lowerBound_
                The lower bound in each dimension.

            \param upperBound_
                The upper bound in each dimension.
         */
        AABB(const Vec2&, const Vec2&);

        /// Compute the surface area of the box.
        float computeSurfaceArea() const;
        /// Get the surface area of the box. ������
        float getSurfaceArea() const;

        //! Merge two AABBs into this one.
        /*! \param aabb1
                A reference to the first AABB.

            \param aabb2
                A reference to the second AABB.
         */
        void merge(const AABB&, const AABB&);

        //! Test whether the AABB is contained within this one.
        /*! \param aabb
                A reference to the AABB.

            \return
                Whether the AABB is fully contained.
         */
        bool contains(const AABB&) const;

        //! Test whether the AABB overlaps this one.
        /*! \param aabb
                A reference to the AABB.

            \param touchIsOverlap
                Does touching constitute an overlap?

            \return
                Whether the AABB overlaps.
         */
        bool overlaps(const AABB&, bool touchIsOverlap) const;

        //! Compute the centre of the AABB.
        /*! \returns
                The position vector of the AABB centre.
         */
        Vec2 computeCentre();

        //! Set the dimensionality of the AABB.
        /*! \param dimension
                The dimensionality of the system.
         */
        //void setDimension(unsigned int);

        /// Lower bound of AABB in each dimension.
        Vec2 lowerBound;

        /// Upper bound of AABB in each dimension.
        Vec2 upperBound;

        /// The position of the AABB centre.
        Vec2 centre;

        /// The AABB's surface area.
        float surfaceArea;
    };

    /*! \brief A node of the AABB tree.

        Each node of the tree contains an AABB object which corresponds to a
        particle, or a group of particles, in the simulation box. The AABB
        objects of individual particles are "fattened" before they are stored
        to avoid having to continually update and rebalance the tree when
        displacements are small.

        Nodes are aware of their position within in the tree. The isLeaf member
        function allows the tree to query whether the node is a leaf, i.e. to
        determine whether it holds a single particle.
     */
    struct ABNode
    {
        /// Constructor.
        ABNode();

        /// The fattened axis-aligned bounding box.
        AABB aabb;

        /// Index of the parent node.
        unsigned int parent;

        /// Index of the next node.
        unsigned int next;

        /// Index of the left-hand child.
        unsigned int left;

        /// Index of the right-hand child.
        unsigned int right;

        /// Height of the node. This is 0 for a leaf and -1 for a free node.
        int height;

        /// The index of the particle that the node contains (leaf nodes only).
        Node* particle;

        //! Test whether the node is a leaf.
        /*! \return
                Whether the node is a leaf node.
         */
        bool isLeaf() const;
    };

    /*! \brief The dynamic AABB tree.

        The dynamic AABB tree is a hierarchical data structure that can be used
        to efficiently query overlaps between objects of arbitrary shape and
        size that lie inside of a simulation box. Support is provided for
        periodic and non-periodic boxes, as well as boxes with partial
        periodicity, e.g. periodic along specific axes.
     */
    class Tree
    {
    public:
        //! Constructor (non-periodic).
        /*! \param dimension_
                The dimensionality of the system.

            \param skinThickness_
                The skin thickness for fattened AABBs, as a fraction
                of the AABB base length.

            \param nParticles
                The number of particles (for fixed particle number systems).

            \param touchIsOverlap
                Does touching count as overlapping in query operations?
         */
        Tree( float skinThickness_ = 0.05,
            unsigned int nParticles = 16, bool touchIsOverlap=true);

        //! Constructor (custom periodicity).
        /*! \param dimension_
                The dimensionality of the system.

            \param skinThickness_
                The skin thickness for fattened AABBs, as a fraction
                of the AABB base length.

            \param periodicity_
                Whether the system is periodic in each dimension.

            \param boxSize_
                The size of the simulation box in each dimension.

            \param nParticles
                The number of particles (for fixed particle number systems).

            \param touchIsOverlap
                Does touching count as overlapping in query operations?
         */
        Tree(float, bool[], const ZY_Size&,
            unsigned int nParticles = 16, bool touchIsOverlap=true);

        //! Set the periodicity of the simulation box.
        /*! \param periodicity_
                Whether the system is periodic in each dimension.
         */
        void setPeriodicity(const bool[]);

        //! Set the size of the simulation box.
        /*! \param boxSize_
                The size of the simulation box in each dimension.
         */
        void setBoxSize(const ZY_Size&);

        //! Insert a particle into the tree (point particle).
        /*! \param index
                The index of the particle.

            \param position
                The position vector of the particle.

            \param radius
                The radius of the particle.
         */
        void insertParticle(Node*, Vec2&, float);

        //! Insert a particle into the tree (arbitrary shape with bounding box).
        /*! \param index
                The index of the particle.

            \param lowerBound
                The lower bound in each dimension.

            \param upperBound
                The upper bound in each dimension.
         */
        void insertParticle(Node*,Vec2&, Vec2&);

        /// Return the number of particles in the tree.
        unsigned int nParticles();

        //! Remove a particle from the tree.
        /*! \param particle
                The particle index (particleMap will be used to map the node).
         */
        void removeParticle(Node*);

        /// Remove all particles from the tree.
        void removeAll();

        //! Update the tree if a particle moves outside its fattened AABB. ��������ƶ������ʵ�AABB֮�⣬�������� 
        /*! \param particle
                The particle index (particleMap will be used to map the node). ��������(particleMap������ӳ��ڵ�)��  

            \param position
                The position vector of the particle. ���ӵ�λ��������

            \param radius
                The radius of the particle. ���ӵİ뾶��

            \param alwaysReinsert
                Always reinsert the particle, even if it's within its old AABB (default:false) �������²������ӣ���ʹ���ھɵ�AABB��(Ĭ��ֵ:false)  

            \return
                Whether the particle was reinserted. �����Ƿ����²��롣
         */
        bool updateParticle(Node*, Vec2&, float, bool alwaysReinsert=false);

        //! Update the tree if a particle moves outside its fattened AABB.
        /*! \param particle
                The particle index (particleMap will be used to map the node).

            \param lowerBound
                The lower bound in each dimension.

            \param upperBound
                The upper bound in each dimension.

            \param alwaysReinsert
                Always reinsert the particle, even if it's within its old AABB (default: false)
         */
        bool updateParticle(Node*, Vec2&, Vec2&, bool alwaysReinsert=false);

        //! Query the tree to find candidate interactions for a particle. ��ѯ�����ҵ����ӵĺ�ѡ������  
        /*! \param particle
                The particle index.

            \return particles
                A vector of particle indices.
         */
        std::vector<Node*> query(Node*);

        //! Query the tree to find candidate interactions for an AABB. ��ѯ�����ҵ�AABB�ĺ�ѡ������  
        /*! \param particle
                The particle index.

            \param aabb
                The AABB.

            \return particles
                A vector of particle indices.
         */
        std::vector<Node*> query(Node*, const AABB&);

        //! Query the tree to find candidate interactions for an AABB.  ��ѯ�����ҵ�AABB�ĺ�ѡ������  
        /*! \param aabb
                The AABB.

            \return particles
                A vector of particle indices.
         */
        std::vector<Node*> query(const AABB&);

        //! Get a particle AABB.
        /*! \param particle
                The particle index.
         */
        const AABB& getAABB(Node*);

        //! Get the height of the tree.
        /*! \return
                The height of the binary tree.
         */
        unsigned int getHeight() const;

        //! Get the number of nodes in the tree.
        /*! \return
                The number of nodes in the tree.
         */
        unsigned int getNodeCount() const;

        //! Compute the maximum balancance of the tree. �����������ƽ�⡣
        /*! \return
                The maximum difference between the height of two
                children of a node.
         */
        unsigned int computeMaximumBalance() const;

        //! Compute the surface area ratio of the tree. �������ı�����ȡ�
        /*! \return
                The ratio of the sum of the node surface area to the surface
                area of the root node. �ڵ�����֮������ڵ�����֮��֮�ȡ�
         */
        float computeSurfaceAreaRatio() const;

        /// Validate the tree. ��֤����
        void validate() const;

        /// Rebuild an optimal tree. �ؽ���������
        void rebuild();

    private:
        /// The index of the root node. ���ڵ��±�
        unsigned int root;

        /// The dynamic tree. ��̬����
        std::vector<ABNode> nodes;

        /// The current number of nodes in the tree. ���е�ǰ�ڵ��������
        unsigned int nodeCount;

        /// The current node capacity. ��ǰ�ڵ�������
        unsigned int nodeCapacity;

        /// The position of node at the top of the free list. �ڵ��ڿ����б�����λ�á�
        unsigned int freeList;

        /// The dimensionality of the system. ϵͳ��ά����
        //unsigned int dimension;

        /// Whether the system is periodic along at least one axis. ϵͳ�Ƿ�������һ�����Ͼ��������ԡ�
        bool isPeriodic;

        /// The skin thickness of the fattened AABBs, as a fraction of the AABB base length. ֬������AABB��Ƥ����ȣ���ΪAABB���׳��ȵ�һ���֡�
        float skinThickness;

        /// Whether the system is periodic along each axis.  ϵͳ�Ƿ���ÿ����������ԡ�
        bool periodicity[2];

        /// The size of the system in each dimension. ÿ��ά����ϵͳ�Ĵ�С��
        ZY_Size boxSize;

        /// The position of the negative minimum image. ������Сͼ���λ�á�
        Vec2 negMinImage;

        /// The position of the positive minimum image. ����Сͼ���λ�á�
        Vec2 posMinImage;

        /// A map between particle and node indices ���Ӻͽڵ�����֮���ӳ�䡣
        std::unordered_map<Node*, unsigned int> particleMap; 
        /// Does touching count as overlapping in tree queries? ������ѯ�д����Ƿ������ص�?
        bool touchIsOverlap;

        //! Allocate a new node.
        /*! \return
                The index of the allocated node.
         */
        unsigned int allocateNode();

        //! Free an existing node.
        /*! \param node
                The index of the node to be freed.
         */
        void freeNode(unsigned int);

        //! Insert a leaf into the tree.
        /*! \param leaf
                The index of the leaf node.
         */
        void insertLeaf(unsigned int);

        //! Remove a leaf from the tree.
        /*! \param leaf
                The index of the leaf node.
         */
        void removeLeaf(unsigned int);

        //! Balance the tree.
        /*! \param node
                The index of the node.
         */
        unsigned int balance(unsigned int);

        //! Compute the height of the tree.
        /*! \return
                The height of the entire tree.
         */
        unsigned int computeHeight() const;

        //! Compute the height of a sub-tree.
        /*! \param node
                The index of the root node.

            \return
                The height of the sub-tree.
         */
        unsigned int computeHeight(unsigned int) const;

        //! Assert that the sub-tree has a valid structure.
        /*! \param node
                The index of the root node.
         */
        void validateStructure(unsigned int) const;

        //! Assert that the sub-tree has valid metrics. ��������������Ч�Ķ�����
        /*! \param node
                The index of the root node.
         */
        void validateMetrics(unsigned int) const;

        //! Apply periodic boundary conditions.Ӧ�������Ա߽�������
        /* \param position
                The position vector.
         */
        void periodicBoundaries(Vec2&);

        //! Compute minimum image separation. ������Сͼ����롣
        /*! \param separation
                The separation vector. ��������

            \param shift
                The shift vector. �仯����

            \return
                Whether a periodic shift has been applied. �Ƿ�Ӧ����������λ��
         */
        bool minimumImage(Vec2&, Vec2&);
    };

#endif /* _AABB_H */