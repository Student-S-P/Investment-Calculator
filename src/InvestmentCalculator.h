/**********************************************************************/
/*! \file  InvestmentCalculator.h
 * \author Seth Peterson
 * \date   2019-10-16
 * \brief
 *     This file contains a class declaration that produces a timeline
 *     showing the progression of an investment on a yearly basis.
 */
/**********************************************************************/

#include "InvestmentData.h" //Data object for history.

class InvestmentCalculator
{
  private:
    double InitialCapital_;
    double InterestRate_;
    double YearlyContribution_;
    InvestmentData* History_;

  public:

    InvestmentCalculator(double InitialCapital, double InterestRate, double YearlyContribution = 1.0);
    ~InvestmentCalculator();

    double PredictGrowth(unsigned YearsToPredict);
    void AddToHistory(double Capital, double Interest, double Contribution);

    void PrintInitialInvestment();
    void PrintInvestmentCumulativeRow(double Capital, double InterestGrowth, double Contribution);

    void SetInitialCapital(double NewCapital);
    void SetInterestRate(double NewRate);
    void SetYearlyContribution(double NewContribution);
    double GetInitialCapital();
    double GetInterestRate();
    double GetYearlyContribution();

    void PrintHistory();
};

double CalculateNextTotal(double InitialCapital, double InterestRate, double YearlyContribution);

void PrintInvestmentLabelRow();
void PrintCumulativeLabelRow();
void PrintHelp();

void PrintInvestmentInformation(int year, double InitialCapital, double InterestGrowth, double Contribution);

