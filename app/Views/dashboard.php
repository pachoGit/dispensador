<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>Bienvenido al dispensador!</title>
    <meta name="description" content="The small framework with powerful features">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="shortcut icon" type="image/png" href="/favicon.ico" />

    <!-- CSS only -->
    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-Zenh87qX5JnK2Jl0vWa8Ck2rdkQ2Bzep5IDxbcnCeuOxjzrPF/et3URy9Bv1WTRi" crossorigin="anonymous">
    <!-- JavaScript Bundle with Popper -->

</head>

<body class="bg-light">

    <div class="container">
        <div class="py-5 text-center">
            <img class="d-block mx-auto mb-4" src="https://getbootstrap.com/docs/4.0/assets/brand/bootstrap-solid.svg" alt="" width="72" height="72">
            <h2>DISPENSADOR EL TIGRILLO</h2>
            <p class="lead">Panel del control del dispensador el Tigrillo, ¡Tus gallinas en nuestras manos¡</p>
        </div>

        <div class="row justify-text-center">
            <div class="col-md-10 order-md-1 offset-md-1">
                <h4 class="mb-3">Estado actual del contenido</h4>
                <form class="needs-validation" novalidate>
                    <div class="row">
                        <div class="col-md-6 mb-3">
                            <label for="grain">Comida</label>
                            <div class="progress mt-2">
                                <div class="progress-bar" id="grain" role="progressbar" aria-label="Label grain" style="width: <?= $percentage['grain_porc'] ?>%;" aria-valuenow="<?= $percentage['grain_porc'] ?>" aria-valuemin="0" aria-valuemax="100"><?= $percentage['grain_porc'] ?>%</div>
                            </div>
                        </div>
                        <div class="col-md-6 mb-3">
                            <label for="water">Agua</label>
                            <div class="progress mt-2">
                                <div class="progress-bar" id="water" role="progressbar" aria-label="Label water" style="width: <?= $percentage['water_porc'] ?>%;" aria-valuenow="<?= $percentage['water_porc'] ?>" aria-valuemin="0" aria-valuemax="100"><?= $percentage['water_porc'] ?>%</div>
                            </div>
                        </div>
                    </div>

                    <div class="row">
                        <div class="col-md-6 mb-3">
                            <?php
                            foreach ($results as $result) {
                                if ($result['id_type'] == '2') {
                            ?>
                                    <div class="row">
                                        <div class="col-md-5 mb-3">
                                            <label for="time_<?= $result['id_detail'] ?>">Hora</label>
                                            <input type="time" class="form-control" id="time_<?= $result['id_detail'] ?>" placeholder="" value="<?= $result['time'] ?>" required readonly>
                                            <div class="invalid-feedback">
                                                Valid first name is required.
                                            </div>
                                        </div>

                                        <div class="col-md-5 mb-3">
                                            <label for="amount_<?= $result['id_config'] ?>">Cantidad</label>
                                            <input type="number" class="form-control" id="amount_<?= $result['id_detail'] ?>" placeholder="" value="<?= $result['amount'] ?>" required readonly>
                                            <div class="invalid-feedback">
                                                Valid first name is required.
                                            </div>
                                        </div>

                                        <div class="col-md-2 mb-3">
                                            <label for=""></label>
                                            <a href="<?= base_url('web/home/delete/' . $result['id_detail']) ?>" class="btn btn-danger mt-4" id="" placeholder="" readonly> - </a>
                                        </div>

                                    </div>
                            <?php }
                            }  ?>
                        </div>

                        <div class="col-md-6 mb-3">
                            <?php
                            foreach ($results as $result) {
                                if ($result['id_type'] == '1') {
                            ?>
                                    <div class="row">
                                        <div class="col-md-5 mb-3">
                                            <label for="time_<?= $result['id_detail'] ?>">Hora</label>
                                            <input type="time" class="form-control" id="time_<?= $result['id_detail'] ?>" placeholder="" value="<?= $result['time'] ?>" required readonly>
                                            <div class="invalid-feedback">
                                                Valid first name is required.
                                            </div>
                                        </div>

                                        <div class="col-md-5 mb-3">
                                            <label for="amount_<?= $result['id_config'] ?>">Cantidad</label>
                                            <input type="number" class="form-control" id="amount_<?= $result['id_detail'] ?>" placeholder="" value="<?= $result['amount'] ?>" required readonly>
                                            <div class="invalid-feedback">
                                                Valid first name is required.
                                            </div>
                                        </div>

                                        <!-- <div class="col-md-2 mb-3">
                                            <label for=""></label>
                                            <a href="<?= base_url('web/home/delete/' . $result['id_detail']) ?>" class="btn btn-danger mt-4" id="" placeholder="" readonly> - </a>
                                        </div> -->
                                    </div>
                            <?php }
                            }  ?>

                        </div>
                    </div>

                    <hr class="mb-4">

                    <div class="row">
                        <div class="col-md-6 mb-3">
                            <button type="button" class="btn btn-primary" data-bs-toggle="modal" data-bs-target="#newGrainModal">
                                Agregar
                            </button>
                        </div>
                        <!-- <div class="col-md-6 mb-3">
                            <button type="button" class="btn btn-primary" data-bs-toggle="modal" data-bs-target="#newWaterModal">
                                Agregar
                            </button>
                        </div> -->
                    </div>

                </form>
            </div>
        </div>

        <!-- Modal -->
        <div class="modal fade" id="newGrainModal" tabindex="-1" aria-labelledby="newGrainModalLabel" aria-hidden="true">
            <div class="modal-dialog">
                <div class="modal-content">
                    <div class="modal-header">
                        <h1 class="modal-title fs-5" id="newGrainModalLabel">Nuevo horario comida</h1>
                        <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                    </div>
                    <form method="post" action="<?= base_url('web/home/create/2') ?>">
                        <div class="modal-body">
                            <div class="row">
                                <div class="col-md-5 mb-3">
                                    <label for="time">Hora</label>
                                    <input type="time" class="form-control" name="time" placeholder="" value="" required>
                                    <div class="invalid-feedback">
                                        El tiempo es necesario
                                    </div>
                                </div>

                                <div class="col-md-5 mb-3">
                                    <label for="amount">Cantidad</label>
                                    <input type="number" class="form-control" name="amount" placeholder="" value="" min="0" required>
                                    <div class="invalid-feedback">
                                        La cantidad es necesario
                                    </div>
                                </div>
                            </div>
                        </div>
                        <div class="modal-footer">
                            <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Cancelar</button>
                            <button type="submit" class="btn btn-primary">Agregar</button>
                        </div>
                    </form>
                </div>
            </div>
        </div>


        <!-- Modal -->
        <div class="modal fade" id="newWaterModal" tabindex="-1" aria-labelledby="newWaterModalLabel" aria-hidden="true">
            <div class="modal-dialog">
                <div class="modal-content">
                    <div class="modal-header">
                        <h1 class="modal-title fs-5" id="newWaterModalLabel">Nuevo horario agua</h1>
                        <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                    </div>
                    <form method="post" action="<?= base_url('web/home/create/1') ?>">
                        <div class="modal-body">
                            <div class="row">
                                <div class="col-md-5 mb-3">
                                    <label for="time">Hora</label>
                                    <input type="time" class="form-control" name="time" placeholder="" value="" required>
                                    <div class="invalid-feedback">
                                        El tiempo es necesario
                                    </div>
                                </div>

                                <div class="col-md-5 mb-3">
                                    <label for="amount">Cantidad</label>
                                    <input type="number" class="form-control" name="amount" placeholder="" value="" min="0" required>
                                    <div class="invalid-feedback">
                                        La cantidad es necesario
                                    </div>
                                </div>
                            </div>
                        </div>
                        <div class="modal-footer">
                            <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Cancelar</button>
                            <button type="submit" class="btn btn-primary">Agregar</button>
                        </div>
                    </form>
                </div>
            </div>
        </div>

        <footer class="my-5 pt-5 text-muted text-center text-small">
            <p class="mb-1">&copy; 2022-2022 Company Name</p>
            <ul class="list-inline">
                <li class="list-inline-item"><a href="#">Privacy</a></li>
                <li class="list-inline-item"><a href="#">Terms</a></li>
                <li class="list-inline-item"><a href="#">Support</a></li>
            </ul>
        </footer>
    </div>

    <script src="https://code.jquery.com/jquery-3.6.1.min.js" integrity="sha256-o88AwQnZB+VDvE9tvIXrMQaPlFFSUTR+nldQm1LuPXQ=" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/js/bootstrap.bundle.min.js" integrity="sha384-OERcA2EqjJCMA+/3y+gxIOqMEjwtxJY7qPCqsdltbNJuaOe923+mo//f6V8Qbsw3" crossorigin="anonymous"></script>
    <script type="text/javascript" src="<?= base_url("js/admin.js") ?>">

    </script>
    <!-- -->

</body>

</html>
