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

  This code was adapted from parts of the Box2D Physics Engine,
  http://www.box2d.org
*/

#include "AABB2.h"


    AABB::AABB()
    {
    }

    //AABB::AABB(unsigned int dimension)
    //{
    //    assert(dimension >= 2);

    //    //lowerBound.resize(dimension);
    //    //upperBound.resize(dimension);
    //}

    AABB::AABB(const Vec2& lowerBound_, const Vec2& upperBound_) :
        lowerBound(lowerBound_), upperBound(upperBound_)
    {
        // Validate the dimensionality of the bounds vectors.
        //if (lowerBound.size() != upperBound.size())
        //{
        //    throw std::invalid_argument("[ERROR]: Dimensionality mismatch!");
        //}

        // Validate that the upper bounds exceed the lower bounds. 验证上界是否超过下界。

        if (lowerBound.x > upperBound.x || lowerBound.y > upperBound.y)
        {
            throw std::invalid_argument("[ERROR]: AABB lower bound is greater than the upper bound!");
        }

        surfaceArea = computeSurfaceArea();
        centre = computeCentre();
    }

    float AABB::computeSurfaceArea() const
    {
        return (lowerBound.x - upperBound.x) * (lowerBound.y - upperBound.y);
    }

    float AABB::getSurfaceArea() const
    {
        return surfaceArea;
    }

    void AABB::merge(const AABB& aabb1, const AABB& aabb2)
    {
        //assert(aabb1.lowerBound.size() == aabb2.lowerBound.size());
        //assert(aabb1.upperBound.size() == aabb2.upperBound.size());

        //lowerBound.resize(aabb1.lowerBound.size());
        //upperBound.resize(aabb1.lowerBound.size());

        lowerBound.x = (std::min)(aabb1.lowerBound.x, aabb2.lowerBound.x);
        lowerBound.y = (std::min)(aabb1.lowerBound.y, aabb2.lowerBound.y);
        upperBound.x = (std::max)(aabb1.upperBound.x, aabb2.upperBound.x);
        upperBound.y = (std::max)(aabb1.upperBound.y, aabb2.upperBound.y);


        surfaceArea = computeSurfaceArea();
        centre = computeCentre();
    }

    bool AABB::contains(const AABB& aabb) const
    {
        //assert(aabb.lowerBound.size() == lowerBound.size());

        if (aabb.lowerBound.x < lowerBound.x || aabb.lowerBound.y < lowerBound.y) return false;
        if (aabb.upperBound.x > upperBound.x || aabb.upperBound.y > upperBound.y) return false;

        return true;
    }

    bool AABB::overlaps(const AABB& aabb, bool touchIsOverlap) const
    {
        //assert(aabb.lowerBound.size() == lowerBound.size());

        bool rv = true;

        if (touchIsOverlap)
        {
            if (aabb.upperBound.x < lowerBound.x ||
                aabb.lowerBound.x > upperBound.x ||
                aabb.upperBound.y < lowerBound.y ||
                aabb.lowerBound.y > upperBound.y)
            {
                rv = false;
            }
        }
        else
        {
            if (aabb.upperBound.x <= lowerBound.x ||
                aabb.lowerBound.x >= upperBound.x ||
                aabb.upperBound.y <= lowerBound.y ||
                aabb.lowerBound.y >= upperBound.y)
            {
                rv = false;
            }
        }

        return rv;
    }

    Vec2 AABB::computeCentre()
    {
        Vec2 position;

        position.x = 0.5f * (lowerBound.x + upperBound.x);
        position.y = 0.5f * (lowerBound.y + upperBound.y);

        return position;
    }

    //void AABB::setDimension(unsigned int dimension)
    //{
    //    assert(dimension >= 2);

    //}

    ABNode::ABNode()
    {
    }

    bool ABNode::isLeaf() const
    {
        return (left == NULL_NODE);
    }

    Tree::Tree(
               float skinThickness_,
               unsigned int nParticles,
               bool touchIsOverlap_) :
        isPeriodic(false), skinThickness(skinThickness_),
        touchIsOverlap(touchIsOverlap_)
    {
        //// Validate the dimensionality.
        //if ((dimension < 2))
        //{
        //    throw std::invalid_argument("[ERROR]: Invalid dimensionality!");
        //}

        // Initialise the periodicity vector.
        periodicity[0] = false;
        periodicity[1] = false;

        // Initialise the tree.
        root = NULL_NODE;
        nodeCount = 0;
        nodeCapacity = nParticles;
        nodes.resize(nodeCapacity);

        // Build a linked list for the list of free nodes. 为空闲节点列表构建一个链表。  
        for (unsigned int i=0;i<nodeCapacity-1;i++)
        {
            nodes[i].next = i + 1;
            nodes[i].height = -1;
        }
        nodes[nodeCapacity-1].next = NULL_NODE;
        nodes[nodeCapacity-1].height = -1;

        // Assign the index of the first free node. 分配第一个空闲节点的索引。
        freeList = 0;
    }

    Tree::Tree(
        float skinThickness_,
        bool periodicity_[],
        const ZY_Size& boxSize_,
        unsigned int nParticles,
        bool touchIsOverlap_) :
        skinThickness(skinThickness_),
        boxSize(boxSize_),
        touchIsOverlap(touchIsOverlap_)
    {
        periodicity[0] = periodicity_[0];
        periodicity[1] = periodicity_[1];

        // Initialise the tree.
        root = NULL_NODE;
        nodeCount = 0;
        nodeCapacity = nParticles;
        nodes.resize(nodeCapacity);

        // Build a linked list for the list of free nodes.
        for (unsigned int i = 0; i < nodeCapacity - 1; i++)
        {
            nodes[i].next = i + 1;
            nodes[i].height = -1;
        }
        nodes[nodeCapacity - 1].next = NULL_NODE;
        nodes[nodeCapacity - 1].height = -1;

        // Assign the index of the first free node.
        freeList = 0;

        // Check periodicity. 检查周期。
        posMinImage = 0.5 * boxSize;
        negMinImage = -0.5 * boxSize;

        isPeriodic = periodicity[0] | periodicity[1];

    }

    void Tree::setPeriodicity(const bool periodicity_[])
    {
        periodicity[0] = periodicity_[0];
        periodicity[1] = periodicity_[1];
    }

    void Tree::setBoxSize(const ZY_Size& boxSize_)
    {
        boxSize = boxSize_;
    }

    unsigned int Tree::allocateNode()
    {
        // Exand the node pool as needed.
        if (freeList == NULL_NODE)
        {
            assert(nodeCount == nodeCapacity);

            // The free list is empty. Rebuild a bigger pool.
            nodeCapacity *= 2;
            nodes.resize(nodeCapacity);

            // Build a linked list for the list of free nodes.
            for (unsigned int i=nodeCount;i<nodeCapacity-1;i++)
            {
                nodes[i].next = i + 1;
                nodes[i].height = -1;
            }
            nodes[nodeCapacity-1].next = NULL_NODE;
            nodes[nodeCapacity-1].height = -1;

            // Assign the index of the first free node.
            freeList = nodeCount;
        }

        // Peel a node off the free list.
        unsigned int node = freeList;
        freeList = nodes[node].next;
        nodes[node].parent = NULL_NODE;
        nodes[node].left = NULL_NODE;
        nodes[node].right = NULL_NODE;
        nodes[node].height = 0;
        nodeCount++;

        return node;
    }

    void Tree::freeNode(unsigned int node)
    {
        assert(node < nodeCapacity);
        assert(0 < nodeCount);

        nodes[node].next = freeList;
        nodes[node].height = -1;
        freeList = node;
        nodeCount--;
    }

    void Tree::insertParticle(Node* particle, Vec2& position, float radius)
    {
        // Make sure the particle doesn't already exist.
        if (particleMap.count(particle) != 0)
        {
            throw std::invalid_argument("[ERROR]: Particle already exists in tree!");
        }

        // Validate the dimensionality of the position vector.
        //if (position.size() != dimension)
        //{
        //    throw std::invalid_argument("[ERROR]: Dimensionality mismatch!");
        //}

        // Allocate a new node for the particle.
        unsigned int node = allocateNode();

        // AABB size in each dimension.
        ZY_Size size;

        // Compute the AABB limits. 计算AABB极限。

        nodes[node].aabb.lowerBound.x = position.x - radius;
        nodes[node].aabb.lowerBound.y = position.y - radius;
        nodes[node].aabb.upperBound.x = position.x + radius;
        nodes[node].aabb.upperBound.y = position.y + radius;
        size = nodes[node].aabb.upperBound - nodes[node].aabb.lowerBound;


        // Fatten the AABB.

        nodes[node].aabb.lowerBound -= skinThickness * size;
        nodes[node].aabb.upperBound += skinThickness * size;

        nodes[node].aabb.surfaceArea = nodes[node].aabb.computeSurfaceArea();
        nodes[node].aabb.centre = nodes[node].aabb.computeCentre();

        // Zero the height.
        nodes[node].height = 0;

        // Insert a new leaf into the tree.
        insertLeaf(node);

        // Add the new particle to the map.
        particleMap.insert(std::unordered_map<Node*, unsigned int>::value_type(particle, node));

        // Store the particle index.
        nodes[node].particle = particle;
    }

    void Tree::insertParticle(Node* particle, Vec2& lowerBound, Vec2& upperBound)
    {
        // Make sure the particle doesn't already exist.
        if (particleMap.count(particle) != 0)
        {
            return;
        }

        //// Validate the dimensionality of the bounds vectors.
        //if ((lowerBound.size() != dimension) || (upperBound.size() != dimension))
        //{
        //    throw std::invalid_argument("[ERROR]: Dimensionality mismatch!");
        //}

        // Allocate a new node for the particle.
        unsigned int node = allocateNode();

        // AABB size in each dimension.
        ZY_Size size;

        // Compute the AABB limits.

            // Validate the bound.
        if (lowerBound.x > upperBound.x || lowerBound.y > upperBound.y)
        {
            throw std::invalid_argument("[ERROR]: AABB lower bound is greater than the upper bound!");
        }

        nodes[node].aabb.lowerBound = lowerBound;
        nodes[node].aabb.upperBound = upperBound;
        size = upperBound - lowerBound;

        // Fatten the AABB.

        nodes[node].aabb.lowerBound -= skinThickness * size;
        nodes[node].aabb.upperBound += skinThickness * size;

        nodes[node].aabb.surfaceArea = nodes[node].aabb.computeSurfaceArea();
        nodes[node].aabb.centre = nodes[node].aabb.computeCentre();

        // Zero the height.
        nodes[node].height = 0;

        // Insert a new leaf into the tree.
        insertLeaf(node);

        // Add the new particle to the map.
        particleMap.insert(std::unordered_map<Node*, unsigned int>::value_type(particle, node));

        // Store the particle index.
        nodes[node].particle = particle;
    }

    unsigned int Tree::nParticles()
    {
        return particleMap.size();
    }

    void Tree::removeParticle(Node* particle)
    {
        // Map iterator.
        std::unordered_map<Node*, unsigned int>::iterator it;

        // Find the particle.
        it = particleMap.find(particle);

        // The particle doesn't exist.
        if (it == particleMap.end())
        {
            return;
        }

        // Extract the node index.
        unsigned int node = it->second;

        // Erase the particle from the map.
        particleMap.erase(it);

        assert(node < nodeCapacity);
        assert(nodes[node].isLeaf());

        removeLeaf(node);
        freeNode(node);
    }

    void Tree::removeAll()
    {
        // Iterator pointing to the start of the particle map.
        std::unordered_map<Node*, unsigned int>::iterator it = particleMap.begin();

        // Iterate over the map.
        while (it != particleMap.end())
        {
            // Extract the node index.
            unsigned int node = it->second;

            assert(node < nodeCapacity);
            assert(nodes[node].isLeaf());

            removeLeaf(node);
            freeNode(node);

            it++;
        }

        // Clear the particle map.
        particleMap.clear();
    }

    bool Tree::updateParticle(Node* particle, Vec2& position, float radius,
        bool alwaysReinsert)
    {
        // Validate the dimensionality of the position vector.
        //if (position.size() != dimension)
        //{
        //    throw std::invalid_argument("[ERROR]: Dimensionality mismatch!");
        //}

        // AABB bounds vectors.
        Vec2 lowerBound;
        Vec2 upperBound;

        // Compute the AABB limits.
        lowerBound.x = position.x - radius;
        lowerBound.y = position.y - radius;
        upperBound.x = position.x + radius;
        upperBound.y = position.y + radius;


        // Update the particle.
        return updateParticle(particle, lowerBound, upperBound, alwaysReinsert);
    }

    bool Tree::updateParticle(Node* particle, Vec2& lowerBound,
        Vec2& upperBound, bool alwaysReinsert)
    {
        // Validate the dimensionality of the bounds vectors.
        //if ((lowerBound.size() != dimension) && (upperBound.size() != dimension))
        //{
        //    throw std::invalid_argument("[ERROR]: Dimensionality mismatch!");
        //}

        // Map iterator.
        std::unordered_map<Node*, unsigned int>::iterator it;

        // Find the particle.
        it = particleMap.find(particle);

        // The particle doesn't exist.
        if (it == particleMap.end())
        {
            return false;
        }

        // Extract the node index.
        unsigned int node = it->second;

        assert(node < nodeCapacity);
        assert(nodes[node].isLeaf());

        // Compute the AABB limits.

            // Validate the bound.
        if (lowerBound.x > upperBound.x || lowerBound.y > upperBound.y)
        {
            throw std::invalid_argument("[ERROR]: AABB lower bound is greater than the upper bound!");
        }

        // AABB size in each dimension.
        ZY_Size size;
        size = upperBound - lowerBound;

        // Create the new AABB.
        AABB aabb(lowerBound, upperBound);

        // No need to update if the particle is still within its fattened AABB.
        if (!alwaysReinsert && nodes[node].aabb.contains(aabb)) return false;

        // Remove the current leaf.
        removeLeaf(node);

        // Fatten the new AABB.

        aabb.lowerBound -= skinThickness * size;
        aabb.upperBound += skinThickness * size;


        // Assign the new AABB.
        nodes[node].aabb = aabb;

        // Update the surface area and centroid.
        nodes[node].aabb.surfaceArea = nodes[node].aabb.computeSurfaceArea();
        nodes[node].aabb.centre = nodes[node].aabb.computeCentre();

        // Insert a new leaf node.
        insertLeaf(node);

        return true;
    }

    std::vector<Node*> Tree::query(Node* particle)
    {
        // Make sure that this is a valid particle.
        if (particleMap.count(particle) == 0)
        {
            throw std::invalid_argument("[ERROR]: Invalid particle index!");
        }

        // Test overlap of particle AABB against all other particles.
        return query(particle, nodes[particleMap.find(particle)->second].aabb);
    }

    std::vector<Node*> Tree::query(Node* particle, const AABB& aabb)
    {
        std::vector<unsigned int> stack;
        stack.reserve(256);
        stack.push_back(root);

        std::vector<Node*> particles;

        while (stack.size() > 0)
        {
            unsigned int node = stack.back();
            stack.pop_back();

            // Copy the AABB.
            AABB nodeAABB = nodes[node].aabb;

            if (node == NULL_NODE) continue;

            if (isPeriodic)
            {
                Vec2 separation;
                Vec2 shift;
                separation = nodeAABB.centre - aabb.centre;

                bool isShifted = minimumImage(separation, shift);

                // Shift the AABB.
                if (isShifted)
                {
                    nodeAABB.lowerBound += shift;
                }
            }

            // Test for overlap between the AABBs.
            if (aabb.overlaps(nodeAABB, touchIsOverlap))
            {
                // Check that we're at a leaf node.
                if (nodes[node].isLeaf())
                {
                    // Can't interact with itself.
                    if (nodes[node].particle != particle)
                    {
                        particles.push_back(nodes[node].particle);
                    }
                }
                else
                {
                    stack.push_back(nodes[node].left);
                    stack.push_back(nodes[node].right);
                }
            }
        }

        return particles;
    }

    std::vector<Node*> Tree::query(const AABB& aabb)
    {
        // Make sure the tree isn't empty.
        if (particleMap.size() == 0)
        {
            return std::vector<Node*>();
        }

        // Test overlap of AABB against all particles.
        return query((std::numeric_limits<Node*>::max)(), aabb);
    }

    const AABB& Tree::getAABB(Node* particle)
    {
        return nodes[particleMap[particle]].aabb;
    }

    void Tree::insertLeaf(unsigned int leaf)
    {
        if (root == NULL_NODE)
        {
            root = leaf;
            nodes[root].parent = NULL_NODE;
            return;
        }

        // Find the best sibling for the node.

        AABB leafAABB = nodes[leaf].aabb;
        unsigned int index = root;

        while (!nodes[index].isLeaf())
        {
            // Extract the children of the node.
            unsigned int left  = nodes[index].left;
            unsigned int right = nodes[index].right;

            float surfaceArea = nodes[index].aabb.getSurfaceArea();

            AABB combinedAABB;
            combinedAABB.merge(nodes[index].aabb, leafAABB);
            float combinedSurfaceArea = combinedAABB.getSurfaceArea();

            // Cost of creating a new parent for this node and the new leaf.
            float cost = 2.f * combinedSurfaceArea;

            // Minimum cost of pushing the leaf further down the tree.
            float inheritanceCost = 2.f * (combinedSurfaceArea - surfaceArea);

            // Cost of descending to the left.
            float costLeft;
            if (nodes[left].isLeaf())
            {
                AABB aabb;
                aabb.merge(leafAABB, nodes[left].aabb);
                costLeft = aabb.getSurfaceArea() + inheritanceCost;
            }
            else
            {
                AABB aabb;
                aabb.merge(leafAABB, nodes[left].aabb);
                float oldArea = nodes[left].aabb.getSurfaceArea();
                float newArea = aabb.getSurfaceArea();
                costLeft = (newArea - oldArea) + inheritanceCost;
            }

            // Cost of descending to the right.
            float costRight;
            if (nodes[right].isLeaf())
            {
                AABB aabb;
                aabb.merge(leafAABB, nodes[right].aabb);
                costRight = aabb.getSurfaceArea() + inheritanceCost;
            }
            else
            {
                AABB aabb;
                aabb.merge(leafAABB, nodes[right].aabb);
                float oldArea = nodes[right].aabb.getSurfaceArea();
                float newArea = aabb.getSurfaceArea();
                costRight = (newArea - oldArea) + inheritanceCost;
            }

            // Descend according to the minimum cost.
            if ((cost < costLeft) && (cost < costRight)) break;

            // Descend.
            if (costLeft < costRight) index = left;
            else                      index = right;
        }

        unsigned int sibling = index;

        // Create a new parent.
        unsigned int oldParent = nodes[sibling].parent;
        unsigned int newParent = allocateNode();
        nodes[newParent].parent = oldParent;
        nodes[newParent].aabb.merge(leafAABB, nodes[sibling].aabb);
        nodes[newParent].height = nodes[sibling].height + 1;

        // The sibling was not the root.
        if (oldParent != NULL_NODE)
        {
            if (nodes[oldParent].left == sibling) nodes[oldParent].left = newParent;
            else                                  nodes[oldParent].right = newParent;

            nodes[newParent].left = sibling;
            nodes[newParent].right = leaf;
            nodes[sibling].parent = newParent;
            nodes[leaf].parent = newParent;
        }
        // The sibling was the root.
        else
        {
            nodes[newParent].left = sibling;
            nodes[newParent].right = leaf;
            nodes[sibling].parent = newParent;
            nodes[leaf].parent = newParent;
            root = newParent;
        }

        // Walk back up the tree fixing heights and AABBs.
        index = nodes[leaf].parent;
        while (index != NULL_NODE)
        {
            index = balance(index);

            unsigned int left = nodes[index].left;
            unsigned int right = nodes[index].right;

            assert(left != NULL_NODE);
            assert(right != NULL_NODE);

            nodes[index].height = 1 + (std::max)(nodes[left].height, nodes[right].height);
            nodes[index].aabb.merge(nodes[left].aabb, nodes[right].aabb);

            index = nodes[index].parent;
        }
    }

    void Tree::removeLeaf(unsigned int leaf)
    {
        if (leaf == root)
        {
            root = NULL_NODE;
            return;
        }

        unsigned int parent = nodes[leaf].parent;
        unsigned int grandParent = nodes[parent].parent;
        unsigned int sibling;

        if (nodes[parent].left == leaf) sibling = nodes[parent].right;
        else                            sibling = nodes[parent].left;

        // Destroy the parent and connect the sibling to the grandparent.
        if (grandParent != NULL_NODE)
        {
            if (nodes[grandParent].left == parent) nodes[grandParent].left = sibling;
            else                                   nodes[grandParent].right = sibling;

            nodes[sibling].parent = grandParent;
            freeNode(parent);

            // Adjust ancestor bounds.
            unsigned int index = grandParent;
            while (index != NULL_NODE)
            {
                index = balance(index);

                unsigned int left = nodes[index].left;
                unsigned int right = nodes[index].right;

                nodes[index].aabb.merge(nodes[left].aabb, nodes[right].aabb);
                nodes[index].height = 1 + (std::max)(nodes[left].height, nodes[right].height);

                index = nodes[index].parent;
            }
        }
        else
        {
            root = sibling;
            nodes[sibling].parent = NULL_NODE;
            freeNode(parent);
        }
    }

    unsigned int Tree::balance(unsigned int node)
    {
        assert(node != NULL_NODE);

        if (nodes[node].isLeaf() || (nodes[node].height < 2))
            return node;

        unsigned int left = nodes[node].left;
        unsigned int right = nodes[node].right;

        assert(left < nodeCapacity);
        assert(right < nodeCapacity);

        int currentBalance = nodes[right].height - nodes[left].height;

        // Rotate right branch up.
        if (currentBalance > 1)
        {
            unsigned int rightLeft = nodes[right].left;
            unsigned int rightRight = nodes[right].right;

            assert(rightLeft < nodeCapacity);
            assert(rightRight < nodeCapacity);

            // Swap node and its right-hand child.
            nodes[right].left = node;
            nodes[right].parent = nodes[node].parent;
            nodes[node].parent = right;

            // The node's old parent should now point to its right-hand child.
            if (nodes[right].parent != NULL_NODE)
            {
                if (nodes[nodes[right].parent].left == node) nodes[nodes[right].parent].left = right;
                else
                {
                    assert(nodes[nodes[right].parent].right == node);
                    nodes[nodes[right].parent].right = right;
                }
            }
            else root = right;

            // Rotate.
            if (nodes[rightLeft].height > nodes[rightRight].height)
            {
                nodes[right].right = rightLeft;
                nodes[node].right = rightRight;
                nodes[rightRight].parent = node;
                nodes[node].aabb.merge(nodes[left].aabb, nodes[rightRight].aabb);
                nodes[right].aabb.merge(nodes[node].aabb, nodes[rightLeft].aabb);

                nodes[node].height = 1 + (std::max)(nodes[left].height, nodes[rightRight].height);
                nodes[right].height = 1 + (std::max)(nodes[node].height, nodes[rightLeft].height);
            }
            else
            {
                nodes[right].right = rightRight;
                nodes[node].right = rightLeft;
                nodes[rightLeft].parent = node;
                nodes[node].aabb.merge(nodes[left].aabb, nodes[rightLeft].aabb);
                nodes[right].aabb.merge(nodes[node].aabb, nodes[rightRight].aabb);

                nodes[node].height = 1 + (std::max)(nodes[left].height, nodes[rightLeft].height);
                nodes[right].height = 1 + (std::max)(nodes[node].height, nodes[rightRight].height);
            }

            return right;
        }

        // Rotate left branch up.
        if (currentBalance < -1)
        {
            unsigned int leftLeft = nodes[left].left;
            unsigned int leftRight = nodes[left].right;

            assert(leftLeft < nodeCapacity);
            assert(leftRight < nodeCapacity);

            // Swap node and its left-hand child.
            nodes[left].left = node;
            nodes[left].parent = nodes[node].parent;
            nodes[node].parent = left;

            // The node's old parent should now point to its left-hand child.
            if (nodes[left].parent != NULL_NODE)
            {
                if (nodes[nodes[left].parent].left == node) nodes[nodes[left].parent].left = left;
                else
                {
                    assert(nodes[nodes[left].parent].right == node);
                    nodes[nodes[left].parent].right = left;
                }
            }
            else root = left;

            // Rotate.
            if (nodes[leftLeft].height > nodes[leftRight].height)
            {
                nodes[left].right = leftLeft;
                nodes[node].left = leftRight;
                nodes[leftRight].parent = node;
                nodes[node].aabb.merge(nodes[right].aabb, nodes[leftRight].aabb);
                nodes[left].aabb.merge(nodes[node].aabb, nodes[leftLeft].aabb);

                nodes[node].height = 1 + (std::max)(nodes[right].height, nodes[leftRight].height);
                nodes[left].height = 1 + (std::max)(nodes[node].height, nodes[leftLeft].height);
            }
            else
            {
                nodes[left].right = leftRight;
                nodes[node].left = leftLeft;
                nodes[leftLeft].parent = node;
                nodes[node].aabb.merge(nodes[right].aabb, nodes[leftLeft].aabb);
                nodes[left].aabb.merge(nodes[node].aabb, nodes[leftRight].aabb);

                nodes[node].height = 1 + (std::max)(nodes[right].height, nodes[leftLeft].height);
                nodes[left].height = 1 + (std::max)(nodes[node].height, nodes[leftRight].height);
            }

            return left;
        }

        return node;
    }

    unsigned int Tree::computeHeight() const
    {
        return computeHeight(root);
    }

    unsigned int Tree::computeHeight(unsigned int node) const
    {
        assert(node < nodeCapacity);

        if (nodes[node].isLeaf()) return 0;

        unsigned int height1 = computeHeight(nodes[node].left);
        unsigned int height2 = computeHeight(nodes[node].right);

        return 1 + (std::max)(height1, height2);
    }

    unsigned int Tree::getHeight() const
    {
        if (root == NULL_NODE) return 0;
        return nodes[root].height;
    }

    unsigned int Tree::getNodeCount() const
    {
        return nodeCount;
    }

    unsigned int Tree::computeMaximumBalance() const
    {
        unsigned int maxBalance = 0;
        for (unsigned int i=0; i<nodeCapacity; i++)
        {
            if (nodes[i].height <= 1)
                continue;

            assert(nodes[i].isLeaf() == false);

            unsigned int balance = std::abs(nodes[nodes[i].left].height - nodes[nodes[i].right].height);
            maxBalance = (std::max)(maxBalance, balance);
        }

        return maxBalance;
    }

    float Tree::computeSurfaceAreaRatio() const
    {
        if (root == NULL_NODE) return 0.0;

        float rootArea = nodes[root].aabb.computeSurfaceArea();
        float totalArea = 0.0;

        for (unsigned int i=0; i<nodeCapacity;i++)
        {
            if (nodes[i].height < 0) continue;

            totalArea += nodes[i].aabb.computeSurfaceArea();
        }

        return totalArea / rootArea;
    }

    void Tree::validate() const
    {
#ifndef NDEBUG
        validateStructure(root);
        validateMetrics(root);

        unsigned int freeCount = 0;
        unsigned int freeIndex = freeList;

        while (freeIndex != NULL_NODE)
        {
            assert(freeIndex < nodeCapacity);
            freeIndex = nodes[freeIndex].next;
            freeCount++;
        }

        assert(getHeight() == computeHeight());
        assert((nodeCount + freeCount) == nodeCapacity);
#endif
    }

    void Tree::rebuild()
    {
        std::vector<unsigned int> nodeIndices(nodeCount);
        unsigned int count = 0;

        for (unsigned int i=0;i<nodeCapacity;i++)
        {
            // Free node.
            if (nodes[i].height < 0) continue;

            if (nodes[i].isLeaf())
            {
                nodes[i].parent = NULL_NODE;
                nodeIndices[count] = i;
                count++;
            }
            else freeNode(i);
        }

        while (count > 1)
        {
            float minCost = (std::numeric_limits<float>::max)();
            int iMin = -1, jMin = -1;

            for (unsigned int i=0;i<count;i++)
            {
                AABB aabbi = nodes[nodeIndices[i]].aabb;

                for (unsigned int j=i+1;j<count;j++)
                {
                    AABB aabbj = nodes[nodeIndices[j]].aabb;
                    AABB aabb;
                    aabb.merge(aabbi, aabbj);
                    float cost = aabb.getSurfaceArea();

                    if (cost < minCost)
                    {
                        iMin = i;
                        jMin = j;
                        minCost = cost;
                    }
                }
            }

            unsigned int index1 = nodeIndices[iMin];
            unsigned int index2 = nodeIndices[jMin];

            unsigned int parent = allocateNode();
            nodes[parent].left = index1;
            nodes[parent].right = index2;
            nodes[parent].height = 1 + (std::max)(nodes[index1].height, nodes[index2].height);
            nodes[parent].aabb.merge(nodes[index1].aabb, nodes[index2].aabb);
            nodes[parent].parent = NULL_NODE;

            nodes[index1].parent = parent;
            nodes[index2].parent = parent;

            nodeIndices[jMin] = nodeIndices[count-1];
            nodeIndices[iMin] = parent;
            count--;
        }

        root = nodeIndices[0];

        validate();
    }

    void Tree::validateStructure(unsigned int node) const
    {
        if (node == NULL_NODE) return;

        if (node == root) assert(nodes[node].parent == NULL_NODE);

        unsigned int left = nodes[node].left;
        unsigned int right = nodes[node].right;

        if (nodes[node].isLeaf())
        {
            assert(left == NULL_NODE);
            assert(right == NULL_NODE);
            assert(nodes[node].height == 0);
            return;
        }

        assert(left < nodeCapacity);
        assert(right < nodeCapacity);

        assert(nodes[left].parent == node);
        assert(nodes[right].parent == node);

        validateStructure(left);
        validateStructure(right);
    }

    void Tree::validateMetrics(unsigned int node) const
    {
        if (node == NULL_NODE) return;

        unsigned int left = nodes[node].left;
        unsigned int right = nodes[node].right;

        if (nodes[node].isLeaf())
        {
            assert(left == NULL_NODE);
            assert(right == NULL_NODE);
            assert(nodes[node].height == 0);
            return;
        }

        assert(left < nodeCapacity);
        assert(right < nodeCapacity);

        int height1 = nodes[left].height;
        int height2 = nodes[right].height;
        int height = 1 + (std::max)(height1, height2);
        (void)height; // Unused variable in Release build
        assert(nodes[node].height == height);

        AABB aabb;
        aabb.merge(nodes[left].aabb, nodes[right].aabb);


        assert(aabb.lowerBound == nodes[node].aabb.lowerBound);
        assert(aabb.upperBound == nodes[node].aabb.upperBound);


        validateMetrics(left);
        validateMetrics(right);
    }

    void Tree::periodicBoundaries(Vec2& position)
    {
        if (position.x < 0)
        {
            position.x += boxSize.width;
        }
        else
        {
            if (position.x >= boxSize.width)
            {
                position.x -= boxSize.width;
            }
        }
        //////////////////////////////////////
        if (position.y < 0)
        {
            position.y += boxSize.height;
        }
        else
        {
            if (position.y >= boxSize.height)
            {
                position.y -= boxSize.height;
            }
        }
    }

    bool Tree::minimumImage(Vec2& separation, Vec2& shift)
    {
        bool isShifted = false;
        if (separation.x < negMinImage.x)
        {
            separation.x += periodicity[0] * boxSize.width;
            shift.x = periodicity[0] * boxSize.width;
            isShifted = true;
        }
        else
        {
            if (separation.x >= posMinImage.x)
            {
                separation.x -= periodicity[0] * boxSize.width;
                shift.x = periodicity[0] * -boxSize.width;
                isShifted = true;
            }
        }
        ///////////////////////////////////////////////////////
        if (separation.y < negMinImage.y)
        {
            separation.y += periodicity[1] * boxSize.height;
            shift.y = periodicity[1] * boxSize.height;
            isShifted = true;
        }
        else
        {
            if (separation.y >= posMinImage.y)
            {
                separation.y -= periodicity[1] * boxSize.height;
                shift.y = -periodicity[1] * boxSize.height;
                isShifted = true;
            }
        }
        return isShifted;
    }

