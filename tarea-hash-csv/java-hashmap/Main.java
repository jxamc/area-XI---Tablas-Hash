import java.io.BufferedReader;
import java.io.FileReader;
import java.util.HashMap;
import java.util.Scanner;

public class Main {

    static HashMap<Integer, Estudiante> estudiantes =
            new HashMap<>();

    static Scanner sc = new Scanner(System.in);

    public static void cargarCSV() {

        try {

            BufferedReader br =
                    new BufferedReader(
                            new FileReader("estudiantes.csv")
                    );

            String linea;

            br.readLine();

            while ((linea = br.readLine()) != null) {

                String[] datos = linea.split(",");

                int id = Integer.parseInt(datos[0]);

                if (estudiantes.containsKey(id)) {

                    System.out.println(
                            "Estudiante duplicado: " + id
                    );

                    continue;
                }

                Estudiante e = new Estudiante(
                        id,
                        datos[1],
                        datos[2],
                        Integer.parseInt(datos[3]),
                        Double.parseDouble(datos[4]),
                        Integer.parseInt(datos[5])
                );

                estudiantes.put(id, e);

                System.out.println(
                        "Cargando estudiante: "
                                + e.studentId
                                + " - "
                                + e.fullName
                );
            }

            br.close();

            System.out.println("\nCarga completada.");

        } catch (Exception e) {

            System.out.println(
                    "Error leyendo estudiantes.csv"
            );
        }
    }

    public static void buscarEstudiante() {

        System.out.print("Ingrese ID: ");

        int id = sc.nextInt();

        if (estudiantes.containsKey(id)) {

            System.out.println(
                    "\n===== ESTUDIANTE ENCONTRADO ====="
            );

            System.out.println(
                    estudiantes.get(id)
            );

        } else {

            System.out.println(
                    "Estudiante no encontrado."
            );
        }
    }

    public static void eliminarEstudiante() {

        System.out.print("Ingrese ID: ");

        int id = sc.nextInt();

        if (estudiantes.containsKey(id)) {

            estudiantes.remove(id);

            System.out.println(
                    "Estudiante eliminado."
            );

        } else {

            System.out.println(
                    "No existe estudiante."
            );
        }
    }

    public static void mostrarEstudiantes() {

        System.out.println(
                "\n===== HASHMAP ESTUDIANTES ====="
        );

        if (estudiantes.isEmpty()) {

            System.out.println("HashMap vacio.");
        }

        for (Integer key : estudiantes.keySet()) {

            System.out.println("----------------");

            System.out.println(
                    estudiantes.get(key)
            );
        }
    }

    public static void mostrarEstadisticas() {

        System.out.println(
                "\n===== ESTADISTICAS ====="
        );

        System.out.println(
                "Total estudiantes: "
                        + estudiantes.size()
        );

        System.out.println(
                "Usando HashMap nativo de Java."
        );
    }

    public static void mostrarMenu() {

        System.out.println("\n===== MENU =====");

        System.out.println("1. Cargar CSV");
        System.out.println("2. Buscar estudiante");
        System.out.println("3. Eliminar estudiante");
        System.out.println("4. Mostrar estudiantes");
        System.out.println("5. Mostrar estadisticas");
        System.out.println("6. Salir");

        System.out.print("Opcion: ");
    }

    public static void main(String[] args) {

        System.out.println(
                "Julio Cesar Xam Chivalan"
        );

        System.out.println(
                "Carnet: 9941-24-8897"
        );

        int opcion;

        do {

            mostrarMenu();

            opcion = sc.nextInt();

            switch (opcion) {

                case 1:

                    cargarCSV();

                    break;

                case 2:

                    buscarEstudiante();

                    break;

                case 3:

                    eliminarEstudiante();

                    break;

                case 4:

                    mostrarEstudiantes();

                    break;

                case 5:

                    mostrarEstadisticas();

                    break;

                case 6:

                    System.out.println(
                            "Saliendo..."
                    );

                    break;

                default:

                    System.out.println(
                            "Opcion invalida."
                    );
            }

        } while (opcion != 6);
    }
}