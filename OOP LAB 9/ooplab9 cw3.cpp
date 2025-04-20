#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class Doctor;
class BillingStaff;

class PatientRecord {
private:
    string name;
    string patientID;
    string dateOfBirth;
    vector<string> medicalHistory;
    vector<string> currentTreatments;
    vector<string> billingRecords;

public:
    PatientRecord(const string& name, const string& id, const string& dob)
        : name(name), patientID(id), dateOfBirth(dob) {}

    string getPublicData() const {
        return "Name: " + name + "\nID: " + patientID + "\nDOB: " + dateOfBirth;
    }

    string getMedicalData() const {
        return "[Medical Data Access Restricted]";
    }

    string getBillingData() const {
        return "[Billing Data Access Restricted]";
    }

    friend class Doctor;
    friend class BillingStaff;
};

class Doctor {
private:
    string doctorID;
    string specialization;

public:
    Doctor(const string& id, const string& spec)
        : doctorID(id), specialization(spec) {}

    string viewMedicalRecord(const PatientRecord& record) const {
        string result = "=== Medical Record (Accessed by Dr. " + doctorID + ") ===\n";
        result += record.getPublicData() + "\n";
        result += "\nMedical History:\n";
        for (const auto& entry : record.medicalHistory) {
            result += "- " + entry + "\n";
        }
        result += "\nCurrent Treatments:\n";
        for (const auto& treatment : record.currentTreatments) {
            result += "- " + treatment + "\n";
        }
        return result;
    }

    void addMedicalHistory(PatientRecord& record, const string& entry) {
        record.medicalHistory.push_back(entry);
    }

    void prescribeTreatment(PatientRecord& record, const string& treatment) {
        record.currentTreatments.push_back(treatment);
    }
};

class BillingStaff {
private:
    string staffID;

public:
    BillingStaff(const string& id) : staffID(id) {}

    string viewBillingInfo(const PatientRecord& record) const {
        string result = "=== Billing Record (Accessed by Staff " + staffID + ") ===\n";
        result += record.getPublicData() + "\n";
        result += "\nBilling Details:\n";
        for (const auto& bill : record.billingRecords) {
            result += "- " + bill + "\n";
        }
        return result;
    }

    void addBillingRecord(PatientRecord& record, const string& bill) {
        record.billingRecords.push_back(bill);
    }
};

class Receptionist {
public:
    string viewPatientInfo(const PatientRecord& record) const {
        return "=== Receptionist View ===\n" + record.getPublicData();
    }

    string attemptMedicalAccess(const PatientRecord& record) const {
        return record.getMedicalData();
    }
};

int main() {
    PatientRecord patient("Ali Khan", "PKR-1024", "1992-07-12");
    Doctor drAhmed("DR-KHI-001", "Cardiology");
    BillingStaff billing("BILL-786");
    Receptionist reception;
    drAhmed.addMedicalHistory(patient, "2018: Angioplasty at Aga Khan University Hospital");
    drAhmed.prescribeTreatment(patient, "Aspirin 75mg daily");
    billing.addBillingRecord(patient, "2024-11-05: Cardiology Checkup - Rs.5000");
    billing.addBillingRecord(patient, "2025-01-10: ECG Test - Rs.1500");
    cout << "\n" << reception.viewPatientInfo(patient) << "\n";
    cout << "\nReceptionist attempts medical access:\n";
    cout << reception.attemptMedicalAccess(patient) << "\n\n";
    cout << drAhmed.viewMedicalRecord(patient) << "\n";
    cout << billing.viewBillingInfo(patient) << "\n";

    return 0;
}
