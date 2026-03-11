#include<stdio.h>

struct process{
    int pid, at, bt, rt, ct, tat, wt;
    int completed;
};

void sjf_nonpreemptive(struct process p[], int n)
{
    int completed=0,time=0,min,index;
    int i;

    for(i=0;i<n;i++) p[i].completed=0;

    while(completed<n){
        min=9999;
        index=-1;

        for(i=0;i<n;i++){
            if(p[i].at<=time && !p[i].completed){
                if(p[i].bt < min){
                    min=p[i].bt;
                    index=i;
                }
                else if(p[i].bt == min && index!=-1){
                    if(p[i].at < p[index].at)
                        index=i;
                }
            }
        }

        if(index!=-1){
            time+=p[index].bt;
            p[index].ct=time;
            p[index].completed=1;
            completed++;
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

    sjf_nonpreemptive(p,n);

    return 0;
}