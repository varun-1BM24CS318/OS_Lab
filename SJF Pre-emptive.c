#include<stdio.h>

struct process{
    int pid, at, bt, rt, ct, tat, wt;
};

void sjf_preemptive(struct process p[], int n)
{
    int completed=0,time=0,min,index;
    int i;

    while(completed<n){
        min=9999;
        index=-1;

        for(i=0;i<n;i++){
            if(p[i].at<=time && p[i].rt>0){
                if(p[i].rt < min){
                    min=p[i].rt;
                    index=i;
                }
                else if(p[i].rt == min && index!=-1){
                    if(p[i].at < p[index].at)
                        index=i;
                }
            }
        }

        if(index!=-1){
            p[index].rt--;
            time++;

            if(p[index].rt==0){
                p[index].ct=time;
                completed++;
            }
        }
        else{
            time++;  // CPU idle
        }
    }

    float avg_tat=0,avg_wt=0;

    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");

    for(i=0;i<n;i++){
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;

        avg_tat+=p[i].tat;
        avg_wt+=p[i].wt;

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,p[i].at,p[i].bt,
               p[i].ct,p[i].tat,p[i].wt);
    }

    printf("\nAverage TAT = %.2f",avg_tat/n);
    printf("\nAverage WT = %.2f",avg_wt/n);
}

int main(){
    int n,i;
    struct process p[20];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        printf("Enter AT and BT for P%d: ",i+1);
        scanf("%d%d",&p[i].at,&p[i].bt);

        p[i].pid=i+1;
        p[i].rt=p[i].bt;
    }

    sjf_preemptive(p,n);

    return 0;
}
