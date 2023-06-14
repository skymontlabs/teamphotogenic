####################### by images #######################
def mean(scores):
	return sum(scores)/len(scores)

def median(scores):
	s = sorted(scores)
	return s[len(s)>>1] if len(s)%2==0 else 0.5 * s[len(s)>>1] + 0.5 * s[len(s)>>1]

def pctile25(scores):
    s = sorted(scores)
    return s[len(s)>>2]

def geomean(scores):
    result = 1
    for x in scores:
        result *= x
    return pow(result, 1/len(scores))

def harmonic(scores):
    s = [1/x for x in scores]
    return len(s)/sum(s)

# len(n) must be # of stars
def bayesian_approx(n, confidence=0.95):
    """
    Function to calculate wilson score for N star rating system. 
    :param n: Array having count of star ratings where ith index represent the votes for that category i.e. [3, 5, 6, 7, 10]
    here, there are 3 votes for 1-star rating, similarly 5 votes for 2-star rating. 
    :param confidence: Confidence interval
    :return: Score
    """
    if sum(n)==0:
        return 0
    K = len(n)
    z = st.norm.ppf(1 - (1 - confidence) / 2)
    N = sum(n)
    first_part = 0.0
    second_part = 0.0
    for k, n_k in enumerate(n):
        first_part += (k+1)*(n[k]+1)/(N+K)
        second_part += (k+1)*(k+1)*(n[k]+1)/(N+K)
    score = first_part - z * math.sqrt((second_part - first_part*first_part)/(N+K+1))
    return score