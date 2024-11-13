#include "SeSchwarzPreconditioner.h"
#include "SeAabbSimd.h"
#include "SeVectorSimd.h"
#include <iostream>
#include <vector>
#include <Eigen/Dense>

// Assume SE_USING_NAMESPACE macro is defined to handle SE_NAMESPACE_BEGIN/END properly
SE_USING_NAMESPACE

int main() {
    // Define some arbitrary sizes for vertices, edges, and faces.
    int numVerts = 10;
    int numEdges = 15;
    int numFaces = 5;

    // Create an instance of SeSchwarzPreconditioner
    SeSchwarzPreconditioner preconditioner;

    // Initialize positions and topology structures
    std::vector<SeVec3fSimd> positions(numVerts, SeVec3fSimd(1.0f, 1.0f, 1.0f)); // Initialize with (1,1,1)
    std::vector<Int4> edges(numEdges, Int4{0, 1, 2, 3}); // Example edge data
    std::vector<Int4> faces(numFaces, Int4{0, 1, 2, -1}); // Example face data
    SeCsr<int> neighbours;

    // Example neighbor data (simple linear connectivity)
    // For a real mesh, populate with actual neighbor indices
    neighbours.data = {1, 2, 3, 4, 0, 2, 3, 0, 1, 3, 0, 1, 2, 4, 0}; 

    // Assign pointers for collision-related data in preconditioner
    preconditioner.m_positions = positions.data();
    preconditioner.m_edges = edges.data();
    preconditioner.m_faces = faces.data();
    preconditioner.m_neighbours = &neighbours;

    // Allocate the preconditioner with the specified mesh size
    preconditioner.AllocatePrecoditioner(numVerts, numEdges, numFaces);

    // Prepare test data for the PreparePreconditioner function
    std::vector<SeMatrix3f> diagonal(numVerts, SeMatrix3f::Identity());
    std::vector<SeMatrix3f> csrOffDiagonals(numVerts, SeMatrix3f());
    std::vector<int> csrRanges(numVerts, 0);
    std::vector<EfSet> efSets;   // Define edge-face sets as needed
    std::vector<EeSet> eeSets;   // Define edge-edge sets as needed
    std::vector<VfSet> vfSets;   // Define vertex-face sets as needed
    std::vector<unsigned int> efCounts(numEdges + 1, 0);
    std::vector<unsigned int> eeCounts(numEdges + 1, 0);
    std::vector<unsigned int> vfCounts(numVerts + 1, 0);

    // Populate efSets, eeSets, vfSets with mock data as needed
    // For simplicity, leaving them empty. In practice, populate with actual data.

    // Prepare the preconditioner with mock input
    preconditioner.PreparePreconditioner(
        diagonal.data(),
        csrOffDiagonals.data(),
        csrRanges.data(),
        efSets.data(),
        eeSets.data(),
        vfSets.data(),
        efCounts.data(),
        eeCounts.data(),
        vfCounts.data()
    );

    // Eigen LDLT Example: Decompose a sample matrix
    Eigen::MatrixXd mat = Eigen::MatrixXd::Random(numVerts, numVerts);
    // Make the matrix symmetric positive definite for LDLT
    mat = mat.transpose() * mat;
    Eigen::VectorXd b = Eigen::VectorXd::Random(numVerts); // Random vector for RHS

    // Perform LDLT decomposition
    Eigen::LDLT<Eigen::MatrixXd> ldlt(mat);
    if (ldlt.info() == Eigen::Success) {
        Eigen::VectorXd x = ldlt.solve(b);
        std::cout << "Solution using Eigen's LDLT decomposition:" << std::endl;
        std::cout << x << std::endl;
    } else {
        std::cerr << "Eigen's LDLT decomposition failed!" << std::endl;
    }

    // Run a test preconditioning operation
    std::vector<SeVec3fSimd> residual(numVerts, SeVec3fSimd(0.5f, 0.5f, 0.5f)); // Placeholder residual values
    std::vector<SeVec3fSimd> z(numVerts);

    preconditioner.Preconditioning(z.data(), residual.data(), numVerts);

    // Output some results for verification
    std::cout << "Output (z vector):" << std::endl;
    for (int i = 0; i < numVerts; ++i) {
        std::cout << "z[" << i << "] = (" << z[i].x << ", " << z[i].y << ", " << z[i].z << ")\n";
    }

    return 0;
}
