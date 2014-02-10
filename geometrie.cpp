//
//  geometrie.cpp
//  Projet Xcode : Planification de trajectoire
//
//  Created by Emmanuel JAY on 07/02/2014.
//  Copyright (c) 2014 Emmanuel JAY. All rights reserved.
//

#include "geometrie.h"

/* FONCTIONS DE LA CLASSE VECTEUR */

    // Constructeurs


vecteur::vecteur(){ // Point de dimension 2 par défaut nul
    dim=2;
    pts = new double[2];
    pts[0] = 0.;pts[1] = 0.;
};
vecteur::vecteur(double x){
    dim=1;
    pts = new double[1];
    pts[0] = x;
}
vecteur::vecteur(double x,double y){
    dim=2;
    pts = new double[2];
    pts[0] = x;pts[1] = y;
}
vecteur::vecteur(double x,double y,double z){
    dim=3;
    pts = new double[3];
    pts[0] = x;pts[1] = y;pts[2]=z;
}
vecteur::vecteur(const vecteur& s){
    dim = s.dim;
    pts = new double[dim];
    for (int i=0; i<dim; i++) {
        pts[i]=s.pts[i];
    }
}
vecteur& vecteur::operator= (const vecteur& s){
    dim = s.dim;
    pts = new double[dim];
    for (int i=0; i<dim; i++) {
        pts[i]=s.pts[i];
    }
    return *this;
}

    // Affichage

std::ostream& operator <<(std::ostream & out,const vecteur & s){
    out<< "(" << s.pts[0];
    for (int i=1; i<s.dim; i++) {
        out << "," << s.pts[i];
    };
    out<< ")";
    return out;
}
void vecteur::print(){
    std::cout<< "(" << pts[0];
    for (int i=1; i<dim; i++) {
        std::cout << "," << pts[i];
    };
    std::cout<< ")";
}

vecteur::vecteur(const sommet& s1,const sommet& s2){
    if (s1.dim!=s2.dim) {
        pts=NULL;
        dim=0;
    }
    else{
        dim = s1.dim;
        pts = new double[dim];
        for (int i=0; i<dim; i++) {
            pts[i]=s2.pts[i]-s1.pts[i];
        }
    }
}

    // Combinaisons linéaires

vecteur & vecteur::operator+=(const vecteur & v){
    
    for (int i=0; i<dim; i++) {
        pts[i]+= v.pts[i];
    };
    
    return *this;
}

vecteur & vecteur::operator+=(const double lambda){
    
    for (int i=0; i<dim; i++) {
        pts[i]+= lambda;
    };
    
    return *this;
}

vecteur & vecteur::operator-=(const vecteur & v){
    
    for (int i=0; i<dim; i++) {
        pts[i]-= v.pts[i];
    };
    
    return *this;
}

vecteur & vecteur::operator-=(const double lambda){
    
    for (int i=0; i<dim; i++) {
        pts[i]-= lambda;
    };
    
    return *this;
}

vecteur & vecteur::operator*=(const double lambda){
    
    for (int i=0; i<dim; i++) {
        pts[i] = pts[i]*lambda;
    };
    
    return *this;
}

vecteur & vecteur::operator/=(const double lambda){
    
    for (int i=0; i<dim; i++) {
        pts[i] = pts[i]/lambda;
    };
    
    return *this;
}

bool operator==(const vecteur & a,const vecteur & b){
    
    if (a.dim!=b.dim) {
        return false;
    }
    
    for (int i=0; (i<a.dim) ; i++) {
        if (a.pts[i]!=b.pts[i]) {
            return false;
        }
    };
    return true;
}

bool operator!=(const vecteur & a,const vecteur & b){
    
    if (a.dim!=b.dim) {
        return true;
    }
    
    for (int i=0; (i<a.dim) ; i++) {
        if (a.pts[i]==b.pts[i]) {
            return false;
        }
    };
    return true;
}

vecteur operator +(const vecteur &a,const vecteur &b){
    vecteur somme(a);
    somme+=b;
    return somme;
}
vecteur operator +(const vecteur &a,const double & lambda){
    vecteur somme(a);
    somme+=lambda;
    return somme;
}
vecteur operator +(const double & lambda,const vecteur &a){
    vecteur somme(a);
    somme+=lambda;
    return somme;
}
vecteur operator -(const vecteur &a,const vecteur &b){
    vecteur dif(a);
    dif-=b;
    return dif;
}
vecteur operator -(const vecteur &a,const double & lambda){
    vecteur dif(a);
    dif-=lambda;
    return dif;
}
vecteur operator -(const double & lambda,const vecteur &a){
    vecteur dif(a);
    dif-=lambda;
    return dif;
}
vecteur operator *(const vecteur &a,const double & lambda){
    vecteur pr(a);
    pr*=lambda;
    return pr;
}
vecteur operator *(const double & lambda,const vecteur &a){
    vecteur pr(a);
    pr*=lambda;
    return pr;
}
vecteur operator /(const vecteur &a,const double & lambda){
    vecteur divi(a);
    divi/=lambda;
    return divi;
}

    // Fonctions Euclidiennes

double ps ( const vecteur & a,const vecteur & b){
    double prosca=0.;
    for (int i=0; i<a.dim; i++) {
        prosca+= a.pts[i]*b.pts[i];
    };
    return prosca;
}

double norm (const vecteur & v){
    return (sqrt(ps(v,v)));
}

vecteur rotation_d2 (const vecteur& v, double theta){
    vecteur vec(v);
    if (v.dim!=2) {
        vec.pts=NULL;
        vec.dim = 0;
        return vec;
    }
    else
    {
        vec.pts[0]= cos(theta)*v.pts[0] - sin(theta)*v.pts[1];
        vec.pts[1]= sin(theta)*v.pts[0] + cos(theta)*v.pts[1];
        return vec;
    }
}

/* FONCTIONS DE LA CLASSE SEGMENT */

    // Constructeurs

segment::segment(const sommet& s1,const sommet& s2){
    S1 = s1;
    S2 = s2;
    n = rotation_d2(vecteur(s1, s2), -PI/2);
    n /= norm(n);
}

    // Affichage

std::ostream& operator <<(std::ostream & out,const segment & s){
    out<< "S1 : " << s.S1 <<" S2 : "<< s.S2 << " n : "<< s.n << "\n";
    return out;
}
