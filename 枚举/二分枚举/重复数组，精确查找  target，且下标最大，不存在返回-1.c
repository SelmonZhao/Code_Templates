int maxIndex(int *nums, int numsSize, int target) {
    int mid, ans = -1;
    int l = 0, r = numsSize-1; 
    while(l <= r) {
        mid = (l + r) >> 1;
        if( target >= nums[mid-1] ) {
            l = mid + 1;                  // (1)
            ans = mid;                    // (2)
        }else {
            r = mid - 1;                  // (3)
        }
    }
    if(ans != -1 && nums[ans-1] != target) {
        ans = -1;                         // (4)
    }
    return ans;                           // (5)
}
/*
* $(1)$ ������```target >= nums[mid-1]```�������������±�һ�������� $[mid, r]$������ $mid$ ���λ����һ�����н⣨���Ž�����������Խ���������СΪ $mid+1$��
* $(2)$ ��¼�¿��н� $mid$ �� $ans$ �У�
* $(3)$ ����```target < nums[mid-1]```�������������±�һ�������� $[l, mid-1]$������������СΪ $mid-1$��
* $(4)$ Ŀǰ�ҵ���λ��ֻ��һ��```target >= nums[ans-1]```��λ�ã����Ե�```target != nums[ans-1]```ʱ��ʵ�������λ������Ч�ģ�������Ҫ��� $-1$��
* $(5)$ ��ʱ��� $ans$ Ϊȫ�����Ž⣬ֱ�ӷ��ؼ��ɡ�
*/
