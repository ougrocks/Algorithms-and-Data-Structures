#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void build(vector<vector<int>>&seg,int c, int l, int r, vector<int>&A)
{
    if(l==r)
    {
        seg[c].push_back(A[r]);
        return;
    }
    int m = (l+r)/2;
    build(seg,2*c,l,m,A);
    build(seg,2*c+1,m+1,r,A);
    merge(seg[c*2].begin(),seg[2*c].end(),seg[2*c+1].begin(),seg[2*c+1].end(),back_inserter(seg[c]));
}

int query(vector<vector<int>>&seg, int c, int l, int r, int L, int R, int k)
{
    if(l>r || l>R || r<L)return 0;
    if(l>=L && r<=R)
        return distance(seg[c].begin(),lower_bound(seg[c].begin(),seg[c].end(),k));

    int m= (l+r)/2;
    return query(seg,2*c,l,m,L,R,k) + query(seg,2*c+1,m+1,r,L,R,k);
}

int main()
{
    ios::sync_with_stdio(0);
    int n,q,L,R,k;
    //cin>>n;
    scanf("%d %d\n",&n,&q);
    vector<int>A(n+1); //note: according to problem all elements are unique
    for(int i=1; i<=n; i++)
        scanf("%d",&A[i]);//cin>>A[i];

    vector<vector<int>>seg(4*n);
    build(seg,1,1,n,A);
    sort(A.begin()+1,A.end());

    //cin>>q;
    while(q--)
    {
        scanf("%d %d %d",&L,&R,&k);
        int l=1,r=n;

        while(l<r)
        {
            int m = (l+r+1)/2;
            int qu = query(seg,1,1,n,L,R,A[m]); //elements < A[m]

            if(qu < k)l=m;
            else r=m-1;
        }

        printf("%d\n",A[r]);
    }
}
