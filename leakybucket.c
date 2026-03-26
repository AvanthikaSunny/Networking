// Congestion control using Leaky Bucket Algorithm
#include <stdio.h>
int main() {
int bucket_size, outgoing_rate, n;
int incoming, stored = 0;
printf("Enter bucket size, outgoing rate and number of inputs: ");
scanf("%d %d %d", &bucket_size, &outgoing_rate, &n);
while (n--) {
printf("\nEnter incoming packet size: ");
scanf("%d", &incoming);
printf("Incoming packet size: %d\n", incoming);
/* Handle incoming packets */
if (incoming + stored <= bucket_size) {
stored += incoming;
} else {
int dropped = (incoming + stored) - bucket_size;
printf("Dropped packets: %d\n", dropped);
stored = bucket_size;
}
printf("Bucket buffer size: %d out of %d\n", stored, bucket_size);
/* Handle outgoing packets */
if (stored >= outgoing_rate) {
stored -= outgoing_rate;
} else {
stored = 0;
}
printf("After outgoing, packets left in buffer: %d out of %d\n",
stored, bucket_size);
}
return 0;
}