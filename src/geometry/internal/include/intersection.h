#pragma once
#include <memory>

#include <structures/rbtree.h>

#include <internal/include/point.h>
#include <internal/include/linesegment.h>

typedef RBTree<PointD, std::vector<LineSegmentD*>> eventQueue;
typedef RBTree<PointD, LineSegmentD*> statusQueue;

void find_neighbours(const PointD& p, RBTree<LineSegmentD*, PointD>& btree, LineSegmentD* &above, LineSegmentD* &below){
    PointD p_sweep = p;
    LineSegmentD s = LineSegment(p_sweep, p_sweep);

    auto it = btree.upperBound(&s);

    if(it == btree.end()){
        above = nullptr;
    }
    else{
        above = (*it).first;
    }

    if(it == btree.begin()){
        below = nullptr;
    }
    else{
        below = (*--it).first;
    }
}

LineSegmentD* find_leftmost(std::vector<LineSegmentD*> &v, const PointD& p){
    LineSegmentD* min = *v.begin();

    for(auto it: v){
        if(it->less(*min, p)){
            min = it;
        }
    }
    return min;
}

LineSegmentD* find_rightmost(std::vector<LineSegmentD*> &v, PointD p){
    LineSegmentD* max = *v.begin();

    for(auto it: v){
        if(max->less(*it, p)){
            max = it;
        }
    }
    return max;
}

LineSegmentD* find_left_neighbour(LineSegmentD* l, RBTree<LineSegmentD*, PointD> &btree){
    auto it = btree.find(l);
    if(it == btree.begin()){
        return nullptr;
    }
    else{
        return (*--it).first;
    }
}

LineSegmentD* find_right_neighbour(LineSegmentD* r, RBTree<LineSegmentD*, PointD> &btree){
    auto it = btree.find(r);
    if(++it == btree.end()){
        return nullptr;
    }
    else{
        return (*it).first;
    }
}

void compute_new_event(LineSegmentD* s0, LineSegmentD* s1, PointD p, statusQueue &status){
    PointD i;
    if(s0 && s1 && s0->intersect(*s1, i)){
        PointD ev_i = i;
        if(p < ev_i && status.find(ev_i) == status.end()){
            status.insert({ev_i, &LineSegmentD()});
        }
    }
}

std::pair<std::vector<LineSegmentD*>, std::vector<LineSegmentD*>> get_sets(PointD p, RBTree<LineSegmentD*, PointD> &btree){
    std::vector<LineSegmentD*> i;
    std::vector<LineSegmentD*> r;

    if(btree.empty()){
        return std::pair<std::vector<LineSegmentD*>, std::vector<LineSegmentD*>>(i, r);
    }

    LineSegmentD* s = new LineSegment(PointD(p.getX(), p.getY()), PointD(p.getX(), p.getY()));

    auto it = btree.upperBound(s);
    RBTree<LineSegmentD*, PointD>::ReverseIterator it_r(it);

    PointD q;
    while(it_r != btree.rend() && (*it_r).first->high(p) == p.getY()){
        if((*it_r).first->contains(p)){
            i.push_back((*it_r).first);
        }
        else if ((*it_r).first->is_rend(p)){
            r.push_back((*it_r).first);
        }
        it_r++;
    }

    return std::pair<std::vector<LineSegmentD*>, std::vector<LineSegmentD*>>(i, r);
}

eventQueue bentley_ottoman(std::vector<LineSegmentD> &set){
    eventQueue inter;
    statusQueue status;

    for(auto line : set)
    {
        PointD left = line.getStart();
        PointD right = line.getEnd();
        status.insert({left, &line});
        status.insert({right, &LineSegmentD()});
    }

    RBTree<LineSegmentD*, PointD> btree;

    while(status.size())
    {
        PointD p = status.begin()->first;
        std::vector<LineSegmentD*> l_set = {status.begin()->second};
        status.erase(status.begin());

        PointD p_sweep = PointD(p.getX(), p.getY());

        std::pair<std::vector<LineSegmentD*>, std::vector<LineSegmentD*>> ir_set = get_sets(p, btree);

        if(l_set.size() + ir_set.first.size() + ir_set.second.size() > 1){
            eventQueue::Iterator it_ev = (inter.insert({p, std::vector<LineSegmentD*>()})).first;
            
            for(auto it_seg: l_set){
                it_ev->second.push_back(it_seg);
            }
            for(auto it_seg: ir_set.first){
                it_ev->second.push_back(it_seg);
            }
            for(auto it_seg: ir_set.second){
                it_ev->second.push_back(it_seg);
            }
        }

        for(auto it_seg: ir_set.first){
            btree.erase(it_seg);
        }
        for(auto it_seg: ir_set.second){
            btree.erase(it_seg);
        }

        p_sweep = Point(p.getX(), p.getY());

        for(auto it_seg: l_set){
            btree.insert({it_seg, p_sweep});
        }
        for(auto it_seg: ir_set.first){
            btree.insert({it_seg, p_sweep});
        }

        if(l_set.size() + ir_set.first.size() == 0){
            LineSegmentD* s_a;
            LineSegmentD* s_b;
            find_neighbours(p, btree, s_a, s_b);
            compute_new_event(s_a, s_b, p, status);
        }

        else{
            std::vector<LineSegmentD*> v(l_set.size() + ir_set.first.size());
            std::set_union(l_set.begin(), l_set.end(), ir_set.first.begin(), ir_set.first.end(), v.begin());
            LineSegmentD* sl = find_leftmost(v, p);
            LineSegmentD* sr = find_rightmost(v, p);
            LineSegmentD* s_a = find_left_neighbour(sl, btree);
            LineSegmentD* s_b = find_right_neighbour(sr, btree);

            compute_new_event(sl, s_b, p, status);
            compute_new_event(sr, s_a, p, status);
        }
    }

    return inter; 
}


